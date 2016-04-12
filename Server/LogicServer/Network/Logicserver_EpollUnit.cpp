#include "Logicserver_EpollUnit.h"

NS_LS_BEGIN


EpollUnit* EpollUnit::instance = NULL;

EpollUnit::EpollUnit()
{
}

EpollUnit* EpollUnit::Instance()
{
    if (instance == NULL)
    {
        instance = new EpollUnit();
    }
    return instance;
}

void EpollUnit::Initialize()
{
    epollfd = Epoll_create(0);
    events = (epoll_event *)calloc(MAXEVENTS, sizeof(struct epoll_event));
    fd_to_func.clear();
}

void EpollUnit::EpollRegist(int32_t connfd, int32_t (*func)(), struct epoll_event * event) 
{
    fd_to_func[connfd] = func;

    if (event == NULL)
    {
        event = new struct epoll_event();
        event->data.fd = connfd;
        event->events = EPOLLIN;
    }
    Epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, event);
}

void EpollUnit::EpollRun()
{
    for (; ; )
    {
        int n = Epoll_wait(epollfd, events, MAXEVENTS, -1);
        for (int i = 0; i < n; i++)
        {
            int fd = events[i].data.fd;
            if ((events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP) ||
                (!(events[i].events & EPOLLIN) && !(events[i].events & EPOLLOUT)))
            {
                err_msg("epoll_run interrupt!");
                EpollDelete(fd);
                continue;
            }

            //check and run function
            if (fd_to_func[fd] == NULL)
            {
                TRACE_WARN("call error: function NULL!");
            }
            else if (fd_to_func[fd]() != success)
            {
                TRACE_WARN("epoll_run registed function error!");
                EpollDelete(fd);
            }
        }
    }
}

void EpollUnit::EpollDelete(int32_t connfd)
{
    fd_to_func[connfd] = NULL;
    Epoll_ctl(epollfd, EPOLL_CTL_DEL, connfd, NULL);
    close(connfd);
}


NS_LS_END
#include "EpollUnit.h"

NS_GJ_BEGIN


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

void EpollUnit::EpollRegist(int32_t connfd, int32_t(*func)(), struct epoll_event * event)
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
                console_msg("call error: function NULL!");
            }
            else if (fd_to_func[fd]() == error)
            {
                console_msg("epoll_run error!");
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

int EpollUnit::Epoll_create(int size = 0)
{
    int ret = 0;
    if ((ret = epoll_create1(size)) < 0)
    {
        console_msg("epoll_create error!");
        return -1;
    }
    return ret;
}

int EpollUnit::Epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
{
    int ret = 0;
    ret = epoll_ctl(epfd, op, fd, event);
    if (ret == -1)
    {
        console_msg("epoll_ctl error!");
        return -1;
    }
    return ret;
}

int EpollUnit::Epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout)
{
    int ret = 0;
    ret = epoll_wait(epfd, events, maxevents, timeout);
    if (ret == -1)
    {
        console_msg("epoll_wait error!");
        return -1;
    }
    return ret;
}

NS_GJ_END
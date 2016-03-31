#include "Connectserver_Common.h"
#include "Connectserver_Socket.h"
#include "Function_Wrap.h"

US_NS_GJ;
US_NS_CS;
US_NS_LG;

int32_t epoll_fd_;
struct epoll_event * events_;

void EpollRegist(int32_t connfd)
{
    struct epoll_event ev;
    ev.data.fd = connfd;
    ev.events = EPOLLIN;
    Epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, connfd, &ev);
}

int main()
{
    ConnsvrSocket* connSocket = ConnsvrSocket::Instance();
    if (error == connSocket->BindAndListen())
    {
        exit(-1);
    }

    epoll_fd_ = Epoll_create(0);
    events_ = (epoll_event *)calloc(MAXEVENTS, sizeof(struct epoll_event));

    EpollRegist(connSocket->GetSocketFd());

    for (; ; )
    {
        int32_t n = Epoll_wait(epoll_fd_, events_, MAXEVENTS, -1);
        for (int32_t i = 0; i < n; ++i)
        {
            int fd = events_[i].data.fd;
            if ((events_[i].events & EPOLLERR) ||
                (events_[i].events & EPOLLHUP) ||
                (!(events_[i].events & EPOLLIN) && !(events_[i].events & EPOLLOUT)))
            {
                TRACE_WARN("a user quit.");
                Epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, NULL);
                connSocket->CloseSocket(fd);
                continue;
            }

            if (fd == connSocket->GetSocketFd())
            {
                std::vector<int32_t> vec;
                int szVec = connSocket->ProcessRequestConnect(vec);
                for (int i = 0; i < szVec; ++i)
                {
                    EpollRegist(vec[i]);
                }
            }
            else
            {
                int32_t rst = connSocket->ProcessRequestTransmitMessage(fd);
                if (error == rst || quit == rst)
                {
                    Epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, NULL);
                    connSocket->CloseSocket(fd);
                }
            }
        }
    }

    return 0;
}
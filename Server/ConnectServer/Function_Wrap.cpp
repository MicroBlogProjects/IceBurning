#include "Function_Wrap.h"

NS_CS_BEGIN

/*******************************socket**********************************/

int Accept(int listenfd, sockaddr * cliaddr, socklen_t * clilen)
{
    int ret;
    if ((ret = accept(listenfd, cliaddr, clilen)) < 0)
    {
        TRACE_WARN("accept error!");
        return -1;
    }
    return ret;
}

int Socket(int family, int type, int protocol)
{
    int ret;
    if ((ret = socket(family, type, protocol)) < 0)
    {
        TRACE_ERROR("Socket error!");
        return -1;
    }
    return ret;
}

int Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
    int ret;
    if ((ret = connect(sockfd, servaddr, addrlen)) < 0)
    {
        TRACE_WARN("connect error!");
        return -1;
    }
    return ret;
}


int Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen)
{
    int ret;
    if ((ret = bind(sockfd, myaddr, addrlen)) < 0)
    {
        TRACE_ERROR("bind error!");
        return -1;
    }
    return ret;
}

int Listen(int sockfd, int backlog)
{
    int ret;
    if ((ret = listen(sockfd, backlog)) < 0)
    {
        TRACE_ERROR("listen error!");
        return -1;
    }
    return ret;
}


/*******************************epoll**********************************/

int Epoll_create(int size = 0)
{
    int ret = 0;
    if ((ret = epoll_create1(size)) < 0)
    {
        TRACE_WARN("epoll_create error!");
        return -1;
    }
    return ret;
}

int Epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
{
    int ret = 0;
    ret = epoll_ctl(epfd, op, fd, event);
    if (ret == -1)
    {
        TRACE_WARN("epoll_ctl error!");
        return -1;
    }
    return ret;
}

int Epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout)
{
    int ret = 0;
    ret = epoll_wait(epfd, events, maxevents, timeout);
    if (ret == -1)
    {
        TRACE_WARN("epoll_wait error!");
        return -1;
    }
    return ret;
}

NS_CS_END
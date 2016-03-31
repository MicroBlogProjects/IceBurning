#pragma once

#ifndef __LOGICSERVER_EPOLLUNIT_H__
#define __LOGICSERVER_EPOLLUNIT_H__

#include "Logicserver_Common.h"
#include <sys/epoll.h>

NS_LS_BEGIN

class EpollUnit {

public:
    static EpollUnit* Instance();
    void Initialize();
    void EpollRegist(int32_t connfd, int32_t (*func)(), struct epoll_event* event = NULL);
    void EpollRun();
    void EpollDelete(int32_t connfd);

private:
    EpollUnit();

private:
    static EpollUnit* instance;
    int32_t epollfd;
    struct epoll_event *events;
    std::map<int32_t, int32_t (*) ()> fd_to_func;
};


NS_LS_END


#endif // !__LOGICSERVER_EPOLLUNIT_H__

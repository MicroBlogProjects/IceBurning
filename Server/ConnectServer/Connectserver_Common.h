#pragma once

#ifndef __CONNECTSERVER_COMMON_H__
#define __CONNECTSERVER_COMMON_H__

#include "Common.h"
#include "Common_Trace.h"
#include "Console_Output.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>

NS_CS_BEGIN

#define PORT 23333
#define LISTENQ 1024
#define SA struct sockaddr
#define MAXEVENTS 64

#define MAXLINE 4096
#define BUFSIZE 8192

#define LOGICSERVER_IP "10.0.128.158"

enum
{
    success = 0,
    error = -1,
    fail = -2,
    quit = -3,
};

NS_CS_END


#endif // !__CONNECTSERVER_COMMON_H__

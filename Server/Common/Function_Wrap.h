#pragma once
#ifndef __FUNCTION_WRAP_H__
#define  __FUNCTION_WRAP_H__

#include "Common.h"
#include "Common_Trace.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>

NS_GJ_BEGIN

#define LISTENQ 1024

int Accept(int listenfd, sockaddr * cliaddr, socklen_t * clilen);
int Socket(int family, int type, int protocol);
int Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
int Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
int Listen(int sockfd, int backlog = LISTENQ);

int Epoll_create(int size);
int Epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
int Epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);

NS_GJ_END


#endif // !__FUNCTION_WRAP_H__

#pragma once
#ifndef __CLIENT_SOCKRT_H__
#define __CLIENT_SOCKRT_H__

#include "my/Common/Common_Head.h"
#include "my/Connect/CMessage.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#define SA struct sockaddr
#else
#include <Winsock2.h>
#endif 


#define CLIENTSOCKET GameJoy::ClientSocket::Instance()

NS_GJ_BEGIN

class ClientSocket
{
public:
    static ClientSocket* Instance();
    int32_t Connect(std::string ip = SERVERIP, int32_t port = SERVERPORT);
    int32_t SendDataToServer(const CMessage& message);
    int32_t RecvOneDataFromServer(CMessage*& message);
    int32_t Initialize();

private:
    ClientSocket() {};
    ~ClientSocket() { delete instance; }

    int32_t MakeSockNonBlock(int32_t fd);
    int32_t RecvMsgsFromServer();
    int32_t RecvOneMessageFromServer(CMessage* message);
    int32_t FillMessage(CMessage* msg);
    int32_t ParseToInt(const char* str, int32_t pBegin, int32_t pEnd);

private:
    static ClientSocket* instance;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    int32_t sockClient;
    struct sockaddr_in addrSrv;
#else
    SOCKET sockClient;
    SOCKADDR_IN addrSrv;

#endif
    std::queue<CMessage*> msg_que;
    int32_t msg_len_;
    int32_t recved_len_;
    int32_t recved_MsgLen_len_;
    int32_t pHead_, pTail_;
    char buf_[MAX_CSMESSAGE_SIZE];
};

NS_GJ_END

#endif // !__CLIENT_SOCKRT_H__
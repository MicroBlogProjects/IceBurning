#pragma once
#ifndef __CLIENT_SOCKRT_H__
#define __CLIENT_SOCKRT_H__

#include "my/Common/Common_Head.h"
#include "CMessage.h"

#include <Winsock2.h>

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
    SOCKET sockClient;
    SOCKADDR_IN addrSrv;

    std::queue<CMessage*> msg_que;
    int32_t msg_len_;
    int32_t recved_len_;
    int32_t recved_MsgLen_len_;
    int32_t pHead_, pTail_;
    char buf_[MAX_CSMESSAGE_SIZE];
};

NS_GJ_END

#endif // !__CLIENT_SOCKRT_H__


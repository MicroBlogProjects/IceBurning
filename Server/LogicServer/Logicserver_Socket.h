#pragma once

#ifndef __LOGICSERVER_SOCKET_H__
#define __LOGICSERVER_SOCKET_H__

#include "Logicserver_Common.h"
#include "Logicserver_Message.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

NS_LS_BEGIN

#define LOGICSOCKET LogicSocket::Instance()

class LogicSocket
{
public:
    static LogicSocket* Instance();

    int32_t ConnectToConnectserver(const std::string& connect_server_ip = "10.0.128.158");
    int32_t WriteMessages(const std::vector<CMessage>& messages);
    int32_t WriteOneMessage(const CMessage& message);
    int32_t ReadMessages(std::vector<CMessage*>& messages);

private:
    LogicSocket();
    void Initialize();

    int32_t ReadOneMessage(CMessage* msg);

    int32_t FillMessage(CMessage* msg);
    int32_t ParseToInt(const char* str, int32_t pBegin, int32_t pEnd);
    int32_t make_socket_non_blocking(int32_t sfd);

private:
    static LogicSocket* instance;

    int32_t logicserver_fd_;

    int32_t msg_len_;
    int32_t recved_len_;
    int32_t recved_MsgLen_len_;
    int32_t pHead_, pTail_;
    char buf_[MAX_CSMESSAGE_SIZE];
};

NS_LS_END

#endif // !__LOGICSERVER_SOCKET_H__

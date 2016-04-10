#pragma once

#ifndef __CONNECTSERVER_SOCKET__
#define __CONNECTSERVER_SOCKET__
#include "Connectserver_Common.h"
#include "Connectserver_Connection.h"

NS_CS_BEGIN

class ConnsvrSocket
{
public:
    static ConnsvrSocket* Instance();

    /*
        initialize
    */
    int32_t BindAndListen();

    int32_t ProcessRequestConnect(std::vector<int32_t>& vec);

    int32_t ProcessRequestTransmitMessage(int32_t fd);

    void CloseSocket(int32_t fd);

    int32_t GetSocketFd();

private:
    //single ton
    ConnsvrSocket();
    static ConnsvrSocket* instance;

    void Initialize();
    bool IsLogicserverConnectRequest(const struct sockaddr_in& _addr);
    bool IsLogicserverConnect(int32_t connfd);

    int32_t TransmitMessageToLogicServer(int32_t client_fd, char* content, int32_t len);
    int32_t TransmitMessageToClient(char* content, int32_t len);

    int32_t make_socket_non_blocking(int32_t sfd);
    int32_t FindMessageSequence(const char* str, int32_t len);
    int32_t ResetMessageSequence(char* str, int32_t new_sq);
    int32_t GeneratNewSequence(int32_t start);
    int32_t FindUin(const char* str, int len);

private:
    // connect server
    int32_t connserver_fd_;
    struct sockaddr_in connserver_addr_;

    // logic server
    int32_t logicserver_fd_;
    bool has_connected_logicserver_;

    // clients
    std::map<int32_t, int32_t> fd_to_msgSequence;
    std::map<int32_t, int32_t> msgSequence_to_fd;
    std::map<int32_t, int32_t> uin_to_fd;
    std::map<int32_t, int32_t> fd_to_uin;

    // read buffer
    std::map<int32_t, CConnConnection> fd_to_conn;

    char buf_[MAX_CSMESSAGE_SIZE];
};

NS_CS_END

#endif // !__CONNECTSERVER_SOCKET__

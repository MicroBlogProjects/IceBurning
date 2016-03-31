#include "Logicserver_Socket.h"

NS_LS_BEGIN

LogicSocket* LogicSocket::instance = NULL;

LogicSocket::LogicSocket()
{
}

LogicSocket* LogicSocket::Instance()
{
    if (instance == NULL)
    {
        instance = new LogicSocket();
    }
    return instance;
}

int32_t LogicSocket::ConnectToConnectserver(const std::string& connect_server_ip)
{
    struct sockaddr_in connServ_addr;

    if ((logicserver_fd_ = Socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        TRACE_ERROR("Socket at ConnectToConnectserver failed");
        return error;
    }

    bzero(&connServ_addr, sizeof(connServ_addr));
    connServ_addr.sin_family = AF_INET;
    connServ_addr.sin_port = htons(CONNECT_SERVER_PORT);
    inet_pton(AF_INET, connect_server_ip.c_str(), &connServ_addr.sin_addr);

    if (Connect(logicserver_fd_, (SA *)&connServ_addr, sizeof(connServ_addr)) < 0)
    {
        TRACE_ERROR("logic server connect to connect server failed.");
        return error;
    }

    make_socket_non_blocking(logicserver_fd_);

    return logicserver_fd_;
}

int32_t LogicSocket::ReadMessages(std::vector<CMessage>& messages)
{

    return success;
}

int32_t LogicSocket::make_socket_non_blocking(int32_t sfd)
{
    int32_t flags, s;
    //得到文件状态标志  
    flags = fcntl(sfd, F_GETFL, 0);
    if (flags == -1)
    {
        TRACE_WARN("fcntl error.");
        return -1;
    }
    //设置文件状态标志  
    flags |= O_NONBLOCK;
    s = fcntl(sfd, F_SETFL, flags);
    if (s == -1)
    {
        TRACE_WARN("fcntl error.");
        return -1;
    }

    return 0;
}
NS_LS_END
#include "Connectserver_Socket.h"

NS_CS_BEGIN

ConnsvrSocket* ConnsvrSocket::instance = NULL;

ConnsvrSocket::ConnsvrSocket()
{
    Initialize();
}

void ConnsvrSocket::Initialize()
{
    logicserver_fd_ = -1;
    has_connected_logicserver_ = false;
    msgSequence_to_fd.clear();
    fd_to_msgSequence.clear();
    uin_to_fd.clear();
    fd_to_uin.clear();
    fd_to_conn.clear();
}

bool ConnsvrSocket::IsLogicserverConnectRequest(const struct sockaddr_in& _addr)
{
    char str[100];
    std::string ip = std::string(inet_ntoa(_addr.sin_addr));
    return ip == LOGICSERVER_IP;
}

bool ConnsvrSocket::IsLogicserverConnect(int32_t connfd)
{
    return connfd == logicserver_fd_;
}

ConnsvrSocket* ConnsvrSocket::Instance()
{
    if (instance == NULL)
    {
        instance = new ConnsvrSocket();
    }
    return instance;
}

void ConnsvrSocket::BindAndListen()
{
    connserver_fd_ = Socket(AF_INET, SOCK_STREAM, 0);

    memset(&connserver_addr_, sizeof(connserver_addr_), 0);
    connserver_addr_.sin_family = AF_INET;
    connserver_addr_.sin_addr.s_addr = htonl(INADDR_ANY);
    connserver_addr_.sin_port = htons(PORT);

    Bind(connserver_fd_, (SA *)&connserver_addr_, sizeof(connserver_addr_));

    Listen(connserver_fd_, LISTENQ);

    make_socket_non_blocking(connserver_fd_);
}

int32_t ConnsvrSocket::ProcessRequestConnect(std::vector<int32_t>& vec)
{
    vec.clear();
    for (; ; )
    {
        struct sockaddr_in temp_sockaddr;
        socklen_t len = sizeof(temp_sockaddr);
        int32_t connfd = Accept(connserver_fd_, (SA*)&temp_sockaddr, &len);
        if (connfd == -1)
        {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
            {
                /* We have processed all incoming connections. */
                break;
            }
            else
            {
                TRACE_WARN("accept error.");
                break;
            }
        }

        make_socket_non_blocking(connfd);
        // give a connection a message buffer
        CConnConnection conn(connfd, temp_sockaddr);
        fd_to_conn[connfd] = conn;

        // connection request of logic server
        if (!has_connected_logicserver_)
        {
            if (!IsLogicserverConnectRequest(temp_sockaddr))
            {
                console_msg("logic server do not connect yet");
                CloseSocket(connfd);
                return -1;
            }
            console_msg("logic server has connected...");
            logicserver_fd_ = connfd;
            has_connected_logicserver_ = true;
        }

        vec.push_back(connfd);
    }
    return vec.size();
}

int32_t ConnsvrSocket::ProcessRequestTransmitMessage(int32_t fd)
{
    char* pMsg;
    int32_t len = sizeof(buf_);
    int status;
    while (success == (status = fd_to_conn[fd].ReadData(buf_, len)))
    {
        // Send message from client to logic server
        if (!IsLogicserverConnect(fd))
        {
            TransmitMessageToLogicServer(fd, buf_, len);
        }
        // send message from logic server to client
        else
        {
            // to do
            //TransmitMessageToClient(buf_, len);
        }
        console_msg(&buf_[4]);
        len = sizeof(buf_);
    }
    if (status == quit)
    {
        if (IsLogicserverConnect(fd))
        {
            console_msg("logic server quit.");
            // TRACE_ERROR("logic server quit.");
            has_connected_logicserver_ = false;
        }
        else
        {
            TRACE_WARN("A user quit with ip(%s)", fd_to_conn[fd].GetIP());
        }
    }
    if (status == error)
    {
        TRACE_WARN("read data error when ProcessRequestTransmitMessage.");
    }
    return status;
}

void ConnsvrSocket::CloseSocket(int32_t fd)
{
    if (fd_to_msgSequence.find(fd) != fd_to_msgSequence.end() &&
        msgSequence_to_fd.find(fd_to_msgSequence[fd]) != msgSequence_to_fd.end())
    {
        msgSequence_to_fd.erase(fd_to_msgSequence[fd]);
        fd_to_msgSequence.erase(fd);
    }
    if (fd_to_uin.find(fd) != fd_to_uin.end() && 
        uin_to_fd.find(fd_to_uin[fd]) != uin_to_fd.end())
    {
        uin_to_fd.erase(fd_to_uin[fd]);
        fd_to_uin.erase(fd);
    }
    fd_to_conn.erase(fd);
    close(fd);
}

int32_t ConnsvrSocket::GetSocketFd()
{
    return connserver_fd_;
}

int32_t ConnsvrSocket::TransmitMessageToLogicServer(int32_t client_fd, char* content, int32_t len)
{
    int32_t uin = FindUin(content, len);
    // save <K, V> of <uin, fd>
    if (uin <= 0)
    {
        int32_t msgID = FindMessageID(content, len);
        if (msgSequence_to_fd.find(msgID) != msgSequence_to_fd.end())
        {
            TRACE_WARN("generated the same msg id.");
            return fail;
        }
        msgSequence_to_fd[msgID] = client_fd;
        fd_to_msgSequence[client_fd] = msgID;
    }
    else if (uin_to_fd.find(uin) == uin_to_fd.end())
    {
        uin_to_fd[uin] = client_fd;
    }
    
    if (error == fd_to_conn[logicserver_fd_].WriteData(content, len))
    {
        TRACE_WARN("transmit content to logic server error.");
        return fail;
    }
    return success;
}

int32_t ConnsvrSocket::TransmitMessageToClient(char* content, int32_t len)
{
    int32_t uin = FindUin(content, len);
    int32_t fd = -1;
    
    // find fd
    if (uin_to_fd.find(uin) == uin_to_fd.end())
    {
        int32_t msgID = FindMessageID(content, len);
        if (msgSequence_to_fd.find(msgID) == msgSequence_to_fd.end())
        {
            TRACE_WARN("can not find fd with msgID(%d) and uin(%d)", msgID, uin);
            return fail;
        }
        fd = msgSequence_to_fd[msgID];

        // msgID only use temporary
        msgSequence_to_fd.erase(msgID);
        fd_to_msgSequence.erase(fd);
    }
    else
    {
        fd = uin_to_fd[uin];
    }

    // find client_connection buffer
    if (fd_to_conn.find(fd) == fd_to_conn.end())
    {
        TRACE_WARN("can not find connection buffer with fd(%d)", fd);
        return fail;
    }
    CConnConnection& client_conn = fd_to_conn[fd];

    // send message
    if (client_conn.WriteData(content, len) < 0)
    {
        TRACE_WARN("transmit content to client failed, connection of user %d disconnect", fd);
        return fail;
    }

    return success;
}

int32_t ConnsvrSocket::make_socket_non_blocking(int32_t sfd)
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

int32_t ConnsvrSocket::FindMessageID(const char* str, int32_t len)
{
    int32_t ret = 0;
    for (int32_t i = 8; i < 12; ++i)
    {
        ret = (ret << 8) | (int32_t)str[i];
    }
    return ret;
}

int32_t ConnsvrSocket::FindUin(const char* str, int len)
{
    int ret = 0;
    for (int32_t i = 4; i < 8; ++i)
    {
        ret = (ret << 8) | (int32_t)str[i];
    }
    return ret;
}

NS_CS_END
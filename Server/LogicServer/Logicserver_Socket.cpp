#include "Logicserver_Socket.h"

NS_LS_BEGIN

LogicSocket* LogicSocket::instance = NULL;

LogicSocket::LogicSocket()
{
    Initialize();
}

void LogicSocket::Initialize()
{
    pHead_ = pTail_ = 0;
    msg_len_ = recved_len_ = 0;
    recved_MsgLen_len_ = 0;
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

int32_t LogicSocket::ReadOneMessage(CMessage* msg)
{
    int32_t sz_int = sizeof(int32_t);
    int32_t recv_byte = 0;
    do 
    {
        // a new mesage coming
        if (recved_MsgLen_len_ < sz_int)
        {
            recv_byte = read(logicserver_fd_, &buf_[pTail_], sz_int - recved_MsgLen_len_);
            if (recv_byte == 0)
            {
                TRACE_WARN("Maybe logic server disconnected with connect server");
                return quit;
            }
            else if (recv_byte < 0)
            {
                if (errno != EAGAIN)
                {
                    TRACE_WARN("read data error.");
                    return error;
                }
                return fail;
            }
            pTail_ = (pTail_ + recv_byte) % MAX_CSMESSAGE_SIZE;
            // 消息头的消息长度字段还没有读完
            if (recv_byte < sz_int - recved_MsgLen_len_)
            {
                recved_MsgLen_len_ += recv_byte;
                return fail;
            }
            // 读完了消息长度字段
            msg_len_ = ParseToInt(buf_, pHead_, pTail_);
            recved_len_ = sz_int;
        }

        // read content except length
        int32_t read_limit = (pTail_ >= pHead_) ? (MAX_CSMESSAGE_SIZE - pTail_) : (pHead_ - pTail_);
        read_limit = std::min(read_limit, msg_len_ - recved_len_);
        recv_byte = read(logicserver_fd_, &buf_[pTail_], read_limit);
        if (recv_byte == 0)
        {
            return quit;
        }
        else if (recv_byte < 0)
        {
            if (errno != EAGAIN)
            {
                TRACE_WARN("read data error.");
                return error;
            }
            return fail;
        }

        recved_len_ += recv_byte;
        pTail_ = (pTail_ + recv_byte) % MAX_CSMESSAGE_SIZE;

        // compelete one message
        if (msg_len_ == recved_len_)
        {
            if (error == FillMessage(msg))
            {
                TRACE_WARN("copy data error.");
                return error;
            }
            msg_len_ = recved_len_ = 0;
            pHead_ = pTail_ = 0;
            recved_MsgLen_len_ = 0;
            return success;
        }
    } while (recv_byte >  0);
}

int32_t LogicSocket::WriteMessages(const std::vector<CMessage>& messages)
{
    for (size_t i = 0; i < messages.size(); ++i)
    {
        if (success != WriteOneMessage(messages[i]))
        {
            TRACE_WARN("Write Message On logic server socket failed.");
            return fail;
        }
    }
    return success;
}

int32_t LogicSocket::WriteOneMessage(const CMessage& message)
{
    char tmp[MAX_CSMESSAGE_SIZE];
    memset(tmp, 0, MAX_CSMESSAGE_SIZE);
    int len = MAX_CSMESSAGE_SIZE;
    if (success != message.Encode(tmp, len))
    {
        TRACE_WARN("Encode message when write one message failed.");
        return fail;
    }
    if (write(logicserver_fd_, tmp, len) < 0)
    {
        TRACE_WARN("write data from logic to connect failed.");
        return fail;
    }
    return success;
}

int32_t LogicSocket::FillMessage(CMessage* msg)
{
    char tmp[MAX_CSMESSAGE_SIZE];
    memset(tmp, 0, MAX_CSMESSAGE_SIZE);
    int len = pHead_ < pTail_ ? (pTail_ - pHead_) : (MAX_CSMESSAGE_SIZE - pHead_ + pTail_);
    if (pHead_ < pTail_)
    {
        memcpy(tmp, &buf_[pHead_], len);
    }
    else
    {
        memcpy(tmp, &buf_[pHead_], MAX_CSMESSAGE_SIZE - pHead_);
        memcpy(&tmp[MAX_CSMESSAGE_SIZE - pHead_], buf_, pTail_);
    }

    return msg->Decode(tmp, len);
}

int32_t LogicSocket::ParseToInt(const char* str, int32_t pBegin, int32_t pEnd)
{
    int32_t ret = 0;
    for (int32_t i = pBegin; i != pEnd; i = (i + 1) % MAX_CSMESSAGE_SIZE)
    {
        ret = (ret << 8) | (int32_t)str[i];
    }
    return ret;
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
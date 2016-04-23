#include "ClientSocket.h"

NS_GJ_BEGIN

ClientSocket* ClientSocket::instance = NULL;

ClientSocket* ClientSocket::Instance()
{
    if (instance == NULL)
    {
        instance = new ClientSocket();
    }
    return instance;
}

int32_t ClientSocket::Initialize()
{
    msg_len_ = 0;
    recved_len_ = 0;
    recved_MsgLen_len_ = 0;
    pHead_ = pTail_ = 0;
    return success;
}

int32_t ClientSocket::Connect(std::string ip, int32_t port)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if ((sockClient = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        CCLOG("socket error.");
        return error;
    }

    bzero(&addrSrv, sizeof(addrSrv));
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &addrSrv.sin_addr);

    if (connect(sockClient, (SA *)&addrSrv, sizeof(addrSrv)) < 0)
    {
        CCLOG("maybe connect to server failed with ip(%s) port(%d)", ip.c_str(), port);
        return error;
    }
#else
    // 加载socket动态链接库(dll)  
    WORD wVersionRequested;
    WSADATA wsaData;    // 这结构是用于接收Wjndows Socket的结构信息的  
    int err;

    wVersionRequested = MAKEWORD(1, 1);   // 请求1.1版本的WinSock库  

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        CCLOG("Initialize in ClientSocket failed.");
        return fail;          // 返回值为零的时候是表示成功申请WSAStartup  
    }

    if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
        // 检查这个低字节是不是1，高字节是不是1以确定是否我们所请求的1.1版本  
        // 否则的话，调用WSACleanup()清除信息，结束函数  
        WSACleanup();
        return fail;
    }

    // 创建socket操作，建立流式套接字，返回套接字号sockClient  
    // SOCKET socket(int af, int type, int protocol);  
    // 第一个参数，指定地址簇(TCP/IP只能是AF_INET，也可写成PF_INET)  
    // 第二个，选择套接字的类型(流式套接字)，第三个，特定地址家族相关协议（0为自动）  
    sockClient = socket(AF_INET, SOCK_STREAM, 0);
    if (sockClient < 0)
    {
        CCLOG("socket error.");
        return fail;
    }

    // 将套接字sockClient与远程主机相连  
    // int connect( SOCKET s,  const struct sockaddr* name,  int namelen);  
    // 第一个参数：需要进行连接操作的套接字  
    // 第二个参数：设定所需要连接的地址信息  
    // 第三个参数：地址的长度  
    addrSrv.sin_addr.S_un.S_addr = inet_addr(ip.c_str());      // 本地回路地址是127.0.0.1;   
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(port);
    if (0 > connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)))
    {
        CCLOG("maybe connect to server failed with ip(%s) port(%d)", ip.c_str(), port);
        return fail;
    }
#endif
    // 设置非阻塞
    MakeSockNonBlock(sockClient);

    return success;
}

int32_t ClientSocket::SendDataToServer(const CMessage& message)
{
    char data[MAX_CSMESSAGE_SIZE];
    memset(data, 0, MAX_CSMESSAGE_SIZE);
    int len = MAX_CSMESSAGE_SIZE;

    if (success != message.Encode(data, len))
    {
        CCLOG("encode msg error when send data to server");
        return fail;
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (write(sockClient, data, len) < 0)
    {
        CCLOG("maybe send msg fail.");
        return fail;
    }
#else
    if (len != send(sockClient, data, len, 0))
    {
        CCLOG("maybe send msg fail.");
        return fail;
    }

#endif
    return success;
}

int32_t ClientSocket::RecvOneDataFromServer(CMessage*& message)
{
    // 先从网络拉取一遍消息
    RecvMsgsFromServer();
    // 再判断队列里有没有消息
    if (!msg_que.empty())
    {
        message = msg_que.front();
        msg_que.pop();
        return success;
    }
    return fail;
}

int32_t ClientSocket::RecvMsgsFromServer()
{
    int ret = fail;
    CMessage* msg = NULL;
    while ( success == ( ret = RecvOneMessageFromServer(msg = new CMessage()) ) )
    {
        msg_que.push(msg);
    }
    delete msg;
    if (ret == quit)
    {
        CCLOG("Maybe ConnServer disconnected.");
        return quit;
    }
    else if (ret == error)
    {
        CCLOG("ReadMessage Error");
        return fail;
    }
    return fail;
}

int32_t ClientSocket::RecvOneMessageFromServer(CMessage* message)
{
    int32_t sz_int = sizeof(int32_t);
    int32_t recv_byte = 0;
    do 
    {
        if (recved_MsgLen_len_ < sz_int)
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            recv_byte = read(sockClient, &buf_[pTail_], sz_int - recved_MsgLen_len_);
#else
            recv_byte = recv(sockClient, &buf_[pTail_], sz_int - recved_MsgLen_len_, 0);
#endif
            if (recv_byte == 0)
            {
                CCLOG("Maybe logic server disconnected with connect server");
                return quit;
            }
            else if (recv_byte < 0)
            {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                if (errno != EAGAIN)
                {
                    CCLOG("read data error.");
                    return error;
                }
                return fail;
#else
                int32_t err = WSAGetLastError();
                if (err != WSAEWOULDBLOCK)
                {
                    CCLOG("read data error.");
                    return error;
                }
                return fail;
#endif
            }
            pTail_ = (pTail_ + recv_byte) % MAX_CSMESSAGE_SIZE;

            if (recv_byte < sz_int - recved_MsgLen_len_)
            {
                recved_MsgLen_len_ += recv_byte;
                return fail;
            }

            msg_len_ = ParseToInt(buf_, pHead_, pTail_);
            recved_len_ = sz_int;
        }

        int32_t read_limit = (pTail_ >= pHead_) ? (MAX_CSMESSAGE_SIZE - pTail_) : (pHead_ - pTail_);
        read_limit = std::min(read_limit, msg_len_ - recved_len_);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        recv_byte = read(sockClient, &buf_[pTail_], read_limit);
#else
        recv_byte = recv(sockClient, &buf_[pTail_], read_limit, 0);
#endif
        if (recv_byte == 0)
        {
            return quit;
        }
        else if (recv_byte < 0)
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            if (errno != EAGAIN)
            {
                CCLOG("read data error.");
                return error;
            }
            return fail;
#else
            int32_t err = WSAGetLastError();
            if (err != WSAEWOULDBLOCK)
            {
                CCLOG("read data error.");
                return error;
            }
            return fail;
#endif
        }

        recved_len_ += recv_byte;
        pTail_ = (pTail_ + recv_byte) % MAX_CSMESSAGE_SIZE;

        // complete one message
        if (msg_len_ == recved_len_)
        {
            if (error == FillMessage(message))
            {
                CCLOG("copy data error.");
                return error;
            }
            msg_len_ = recved_len_ = 0;
            pHead_ = pTail_ = 0;
            recved_MsgLen_len_ = 0;
            return success;
        }
    } while (recv_byte > 0);
    return fail;
}

int32_t ClientSocket::FillMessage(CMessage* msg)
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

int32_t ClientSocket::ParseToInt(const char* str, int32_t pBegin, int32_t pEnd)
{
    int32_t ret = 0;
    for (int32_t i = pBegin; i != pEnd; i = (i + 1) % MAX_CSMESSAGE_SIZE)
    {
        ret = (ret << 8) | (unsigned char)(str[i] & 0x000000ff);
    }
    return ntohl(ret);
}

int32_t ClientSocket::MakeSockNonBlock(int32_t fd)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    int32_t flags, s;
    flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
    {
        return -1;
    }
    flags |= O_NONBLOCK;
    s = fcntl(fd, F_SETFL, flags);
    if (s == -1)
    {
        return -1;
    }
    return success;
#else
    int32_t iMode = 1;
    ioctlsocket(fd, FIONBIO, (u_long FAR*)&iMode);
    return success;
#endif
}

NS_GJ_END
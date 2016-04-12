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
    // ����socket��̬���ӿ�(dll)  
    WORD wVersionRequested;
    WSADATA wsaData;    // ��ṹ�����ڽ���Wjndows Socket�Ľṹ��Ϣ��  
    int err;

    wVersionRequested = MAKEWORD(1, 1);   // ����1.1�汾��WinSock��  

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        console_msg("Initialize in ClientSocket failed.");
        return fail;          // ����ֵΪ���ʱ���Ǳ�ʾ�ɹ�����WSAStartup  
    }

    if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
        // ���������ֽ��ǲ���1�����ֽ��ǲ���1��ȷ���Ƿ������������1.1�汾  
        // ����Ļ�������WSACleanup()�����Ϣ����������  
        WSACleanup();
        return fail;
    }

    // ����socket������������ʽ�׽��֣������׽��ֺ�sockClient  
    // SOCKET socket(int af, int type, int protocol);  
    // ��һ��������ָ����ַ��(TCP/IPֻ����AF_INET��Ҳ��д��PF_INET)  
    // �ڶ�����ѡ���׽��ֵ�����(��ʽ�׽���)�����������ض���ַ�������Э�飨0Ϊ�Զ���  
    sockClient = socket(AF_INET, SOCK_STREAM, 0);
    if (sockClient < 0)
    {
        console_msg("socket error.");
        return fail;
    }

    // ���׽���sockClient��Զ����������  
    // int connect( SOCKET s,  const struct sockaddr* name,  int namelen);  
    // ��һ����������Ҫ�������Ӳ������׽���  
    // �ڶ����������趨����Ҫ���ӵĵ�ַ��Ϣ  
    // ��������������ַ�ĳ���  
    addrSrv.sin_addr.S_un.S_addr = inet_addr(ip.c_str());      // ���ػ�·��ַ��127.0.0.1;   
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(port);
    if (0 > connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)))
    {
        console_msg("maybe connect to server failed with ip(%s) port(%d)", ip.c_str(), port);
        return fail;
    }
    // ���÷�����
    MakeSockNonBlock(sockClient);

    console_msg("connect success.");
    return success;
}

int32_t ClientSocket::SendDataToServer(const CMessage& message)
{
    char data[MAX_CSMESSAGE_SIZE];
    memset(data, 0, MAX_CSMESSAGE_SIZE);
    int len = MAX_CSMESSAGE_SIZE;

    if (success != message.Encode(data, len))
    {
        console_msg("encode msg error when send data to server");
        return fail;
    }
    if (len != send(sockClient, data, len, 0))
    {
        console_msg("maybe send msg fail.");
        return fail;
    }

    return success;
}

int32_t ClientSocket::RecvOneDataFromServer(CMessage*& message)
{
    // �ȴ�������ȡһ����Ϣ
    RecvMsgsFromServer();
    // ���ж϶�������û����Ϣ
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
        console_msg("Maybe ConnServer disconnected.");
        return quit;
    }
    else if (ret == error)
    {
        console_msg("ReadMessage Error");
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
            recv_byte = recv(sockClient, &buf_[pTail_], sz_int - recved_MsgLen_len_, 0);
            if (recv_byte == 0)
            {
                console_msg("Maybe logic server disconnected with connect server");
                return quit;
            }
            else if (recv_byte < 0)
            {
                int32_t err = WSAGetLastError();
                if (err != WSAEWOULDBLOCK)
                {
                    console_msg("read data error.");
                    return error;
                }
                return fail;
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
        recv_byte = recv(sockClient, &buf_[pTail_], read_limit, 0);
        if (recv_byte == 0)
        {
            return quit;
        }
        else if (recv_byte < 0)
        {
            int32_t err = WSAGetLastError();
            if (err != WSAEWOULDBLOCK)
            {
                console_msg("read data error.");
                return error;
            }
            return fail;
        }

        recved_len_ += recv_byte;
        pTail_ = (pTail_ + recv_byte) % MAX_CSMESSAGE_SIZE;

        // complete one message
        if (msg_len_ == recved_len_)
        {
            if (error == FillMessage(message))
            {
                console_msg("copy data error.");
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
        ret = (ret << 8) | (int32_t)str[i];
    }
    return ntohl(ret);
}

int32_t ClientSocket::MakeSockNonBlock(int32_t fd)
{
    int32_t iMode = 1;
    ioctlsocket(fd, FIONBIO, (u_long FAR*)&iMode);
    return success;
}

NS_GJ_END


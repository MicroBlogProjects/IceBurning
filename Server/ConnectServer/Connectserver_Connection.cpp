#include "Connectserver_Connection.h"

NS_CS_BEGIN


CConnConnection::CConnConnection(int32_t connfd, const struct sockaddr_in& addr)
{
    connfd_ = connfd;
    pHead_ = pTail_ = 0;
    msg_len_ = recved_len_ = -1;
    recved_MsgLen_len_ = 0;
    addr_ = addr;
}

// read data from connfd_ :
//    if complete one message then return success and out_str can has been filled
//    if do not finish return fail and out_str is not filled
//    if user disconnect return quit
//    if read error return error
int32_t CConnConnection::ReadData(char* out_str, int32_t& str_size)
{
    char* str = out_str;
    const int32_t sz_int = sizeof(int32_t);
    int32_t recv_byte = 0;
    do {
        // a new mesage coming
        if (recved_MsgLen_len_ < sz_int)
        {
            recv_byte = recv(connfd_, &buf_[pTail_], sz_int - recved_MsgLen_len_,0);
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
        recv_byte = recv(connfd_, &buf_[pTail_], read_limit, 0);
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
            if (error == CopyData(str, str_size))
            {
                TRACE_WARN("copy data error.");
                return error;
            }
            str_size = msg_len_;
            msg_len_ = recved_len_ = -1;
            pHead_ = pTail_ = 0;
            recved_MsgLen_len_ = 0;
            return success;
        }
    } while (recv_byte > 0);

    return fail;
}

// write data with size of size
int32_t CConnConnection::WriteData(const char* str, int32_t size)
{
    if (send(connfd_, str, size, 0) < 0 && errno != EAGAIN)
    {
        return error;
    }
    return success;
}

int32_t CConnConnection::CopyData(char* dst, int dst_size)
{
    memset(dst, 0, dst_size);
    int32_t len = pHead_ < pTail_ ? (pTail_ - pHead_) : (MAX_CSMESSAGE_SIZE - pHead_ + pTail_);
    if (len > dst_size)
    {
        TRACE_WARN("buffer size too small.");
        return error;
    }
    if (pHead_ < pTail_)
    {
        memcpy(dst, &buf_[pHead_], len);
    }
    else
    {
        memcpy(dst, &buf_[pHead_], MAX_CSMESSAGE_SIZE - pHead_);
        memcpy(&dst[MAX_CSMESSAGE_SIZE - pHead_], buf_, pTail_);
    }
    return success;
}

int32_t CConnConnection::ParseToInt(const char* str, int32_t pBegin, int32_t pEnd)
{
    int32_t ret = 0;
    for (int32_t i = pBegin; i != pEnd; i = (i + 1) % MAX_CSMESSAGE_SIZE)
    {
        ret = (ret << 8) | (unsigned char)str[i];
    }
    return ntohl(ret);
}

const char* CConnConnection::GetIP()
{
    char str[100];
    return inet_ntop(AF_INET, &addr_, str, sizeof(str));
}


NS_CS_END


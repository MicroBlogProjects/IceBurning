#pragma once

#ifndef __CONNECTSERVER_CONNECTION_H__
#define __CONNECTSERVER_CONNECTION_H__
#include "Connectserver_Common.h"

NS_CS_BEGIN

class CConnConnection
{
public:
    CConnConnection();
    CConnConnection(int32_t connfd, const struct sockaddr_in& addr);
    
    int32_t ReadData(char* str, int32_t& str_size);
    int32_t WriteData(const char* str, int32_t size);

    const char* GetIP();

private:
    int32_t CopyData(char* dst, int dst_size);
    int32_t ParseToInt(const char* str, int32_t pBegin, int32_t pEnd);

private:
    int32_t connfd_;
    struct sockaddr_in addr_;
    
    int32_t msg_len_;
    int32_t recved_len_;
    int32_t recved_MsgLen_len_;
    char buf_[MAX_CSMESSAGE_SIZE];
    int32_t pHead_, pTail_;
};

NS_CS_END

#endif // !__CONNECTSERVER_CONNECTION_H__

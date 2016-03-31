#pragma once
#ifndef __LOGICSERVER_MESSAGE_H__
#define __LOGICSERVER_MESSAGE_H__

#include "Logicserver_Common.h"
#include <google/protobuf/message.h>

NS_LS_BEGIN

class CMessageHead
{
public:
    int32_t Encode(char* out_str, int32_t& out_len);
    int32_t Decode(const char* in_str, int32_t in_len);

    int32_t Size();

private:
    int32_t EncodeInt32(char*& str, int32_t value);
    int32_t DecodeInt32(const char*& str);

private:
    int32_t m_iMessageLen;      //这个是整个包的长度，包括此字段
    int32_t m_iUin;             //当没有登录时，没有uin，需要将此项填充为<=0
    int32_t m_iMessageID;       //消息类型
    int32_t m_iMessageSequece;  //消息唯一标识符
};

class CMessageBody
{
public:
    int32_t Encode(char* out_str, int32_t& out_len);
    int32_t Decode(const char* in_str, int32_t in_len);

private:
    ::google::protobuf::Message *message;
};

class CMessage
{
public:
    // return: success or fail
    int32_t Encode(char* out_str, int32_t& out_len);
    int32_t Decode(const char* in_str, int32_t in_len);
private:
    CMessageHead m_iMessageHead;
    CMessageBody m_iMessageBody;
};


NS_LS_END


#endif // !__LOGICSERVER_MESSAGE_H__
#pragma once
#ifndef __CMESSAGE_H__
#define __CMESSAGE_H__

#include "my/Common/Common_Head.h"
#include "google/protobuf/message.h"
#include <fcntl.h>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <arpa/inet.h>
#endif

NS_GJ_BEGIN

class CMessageHead
{
public:
    CMessageHead(int32_t uin = -1, int32_t msgID = -1)
        :m_iUin(uin), m_iMessageID(msgID) {}

    int32_t Encode(char* out_str, int32_t& out_len) const;
    int32_t Decode(const char* in_str, int32_t in_len);
    int32_t Size() const;

    void SetLen(int32_t len) { this->m_iMessageLen = len; }
    void SetUin(int32_t uin) { this->m_iUin = uin; }
    void SetMid(int32_t mid) { this->m_iMessageID = mid; }
    void SetMsq(int32_t msq) { this->m_iMessageSequece = msq; }
    int32_t GetLen() { return m_iMessageLen; }
    int32_t GetUin() { return m_iUin; }
    int32_t GetMid() { return m_iMessageID; }
    int32_t GetMsq() { return m_iMessageSequece; }
private:
    int32_t EncodeInt32(char*& str, int32_t value) const;
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
    ~CMessageBody();

    int32_t Encode(char* out_str, int32_t& out_len) const;
    int32_t Decode(const char* in_str, int32_t in_len);

    template<class PB_T> static CMessageBody* ConstructMessageBody()
    {
        CMessageBody* messageBody = new CMessageBody();
        messageBody->message = new PB_T();
        return messageBody;
    }
    ::google::protobuf::Message* GetPB()
    {
        return message;
    }
private:
    CMessageBody() {}
    ::google::protobuf::Message* message;
};

class CMessage
{
public:
    CMessage():m_iMessageHead(NULL), m_iMessageBody(NULL) {}
    ~CMessage();
    // return: success or fail
    int32_t Encode(char* out_str, int32_t& out_len) const;
    int32_t Decode(const char* in_str, int32_t in_len);

    void SetMessageHead(CMessageHead* head);
    void SetMessageBody(CMessageBody* body);

    ::google::protobuf::Message* GetPB() { return m_iMessageBody->GetPB(); }
    int32_t GetUin() { return m_iMessageHead->GetUin(); }
    int32_t GetMessageID() { return m_iMessageHead->GetMid(); }

private:
    CMessageHead* m_iMessageHead;
    CMessageBody* m_iMessageBody;
};


NS_GJ_END

#endif // !__CMESSAGE_H__
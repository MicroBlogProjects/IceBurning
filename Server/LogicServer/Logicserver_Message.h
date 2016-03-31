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
    int32_t m_iMessageLen;      //������������ĳ��ȣ��������ֶ�
    int32_t m_iUin;             //��û�е�¼ʱ��û��uin����Ҫ���������Ϊ<=0
    int32_t m_iMessageID;       //��Ϣ����
    int32_t m_iMessageSequece;  //��ϢΨһ��ʶ��
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
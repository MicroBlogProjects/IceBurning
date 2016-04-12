
#include "CMessage.h"
#include "my/ProtoOut/MessageRegister.h"

NS_GJ_BEGIN

int32_t CMessageHead::Encode(char* out_str, int32_t& out_len) const
{
    if (out_len < Size())
    {
        console_msg("char array length too short when Encode message head.");
        return fail;
    }

    char* str = out_str;
    int32_t len = 0;
    len += EncodeInt32(str, m_iMessageLen);
    len += EncodeInt32(str, m_iUin);
    len += EncodeInt32(str, m_iMessageID);
    len += EncodeInt32(str, m_iMessageSequece);
    out_len = len;
    return success;
}

int32_t CMessageHead::Decode(const char* in_str, int32_t in_len)
{
    if (in_len < Size())
    {
        console_msg("char array length is too short when decode message head");
        return fail;
    }
    int32_t len = 0;
    const char* str = in_str;

    m_iMessageLen       = DecodeInt32(str);
    m_iUin              = DecodeInt32(str);
    m_iMessageID        = DecodeInt32(str);
    m_iMessageSequece   = DecodeInt32(str);
    return success;
}

int32_t CMessageHead::Size() const
{
    return sizeof(int32_t) * 4;
}

int32_t CMessageHead::EncodeInt32(char*& str, int32_t value) const
{
    int32_t p = 0xff000000;
    value = htonl(value);
    int w = 24;
    for (int i = 0; i < sizeof(int32_t); ++i)
    {
        *(str++) = (char)((value & p) >> w);
        p >>= 8;
        w -= 8;
    }
    return sizeof(int32_t);
}

int32_t CMessageHead::DecodeInt32(const char*& str)
{ 
    int32_t value = 0;
    for (int32_t i = 0; i < sizeof(int32_t); ++i)
    {
        value = (value << 8) | (int32_t)*(str++);
    }
    value = ntohl(value);
    return value;
}


CMessageBody::~CMessageBody()
{
    delete message;
}

int32_t CMessageBody::Encode(char* out_str, int32_t& out_len) const
{
    if (false == message->SerializeToArray(out_str, out_len))
    {
        return fail;
    }
    out_len = message->ByteSize();
    return success;
}

int32_t CMessageBody::Decode(const char* in_str, int32_t in_len)
{
    if (!message->ParseFromArray(in_str, in_len))
    {
        console_msg("parse message from array failed.");
        return fail;
    }
    return success;
}


CMessage::~CMessage()
{
    if (m_iMessageHead != NULL)
    {
        delete m_iMessageHead;
    }
    if (m_iMessageBody != NULL)
    {
        delete m_iMessageBody;
    }
}

int32_t CMessage::Encode(char* out_str, int32_t& out_len) const
{
    char* str = out_str;

    int32_t head_len = out_len;
    int32_t result = m_iMessageHead->Encode(str, head_len);
    if (result == fail)
    {
        console_msg("encode messgae head failed.");
        return fail;
    }

    int32_t body_len = out_len - head_len;
    result = m_iMessageBody->Encode(&str[head_len], body_len);
    if (result == fail)
    {
        console_msg("encode messgae body failed.");
        return fail;
    }

    out_len = head_len + body_len;
    return success;
}

int32_t CMessage::Decode(const char* in_str, int32_t in_len)
{
    // 解析消息头
    if (m_iMessageHead == NULL)
    {
        m_iMessageHead = new CMessageHead();
    }
    int32_t head_len = m_iMessageHead->Size();
    if (fail == m_iMessageHead->Decode(in_str, head_len))
    {
        console_msg("decode message head fail.");
        return fail;
    }

    // 根据消息头的msgID生成对应的body，然后解析
    if (m_iMessageBody == NULL)
    {
        // 这里客户端的代码默认为decode时使用responsePB
        m_iMessageBody = NewResponseBodtWithMsgID(m_iMessageHead->GetMid());
    }
    int32_t body_len = in_len - head_len;
    if (fail == m_iMessageBody->Decode(&in_str[head_len], body_len))
    {
        console_msg("decode message body fail.");
        return fail;
    }
    return success;
}

void CMessage::SetMessageHead(CMessageHead* head)
{
    m_iMessageHead = head;
}

void CMessage::SetMessageBody(CMessageBody* body)
{
    m_iMessageBody = body;
    m_iMessageHead->SetLen(m_iMessageHead->Size() + m_iMessageBody->GetPB()->ByteSize());
    m_iMessageHead->SetMsq((int32_t)(time(NULL) << 16) | (1 + rand()));
}

NS_GJ_END

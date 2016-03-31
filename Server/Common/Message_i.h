#pragma once

#ifndef __MESSAGE_I_G__
#define __MESSAGE_I_G__

/*

class CMessageHead
{
    int32_t m_iPackageLen;      //这个是整个包的长度，包括此字段
    int32_t m_iUin;             //当没有登录时，没有uin，需要将此项填充为<=0
    int32_t m_iMessageID;       //消息类型
    int32_t m_iMessageSequece;  //消息唯一标识符
}
*/

/***************************message ID end*********************************/

#define MSG_ON_LOGIN                0x0001 // 登录请求
#define MSG_ON_REGIST               0x0002 // 注册请求


/***************************message ID end*********************************/

#endif // !__MESSAGE_I_G__

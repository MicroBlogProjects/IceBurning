#include "MessageRegister.h"
#include "Message_i.h"

/*==========================添加要注册的PB的头文件及注册===========================*/
// 登录协议
#include "Login.pb.h"
RegistPBToMessageID(MSG_ON_LOGIN, CSLoginRequest, CSLoginResponse)

// to add 其他协议
/*==============================================================================*/

NS_GJ_BEGIN

MsgRegister* MsgRegister::instance = NULL;

MsgRegister* MsgRegister::Instance()
{
    if (instance == NULL)
    {
        instance = new MsgRegister();
    }
    return instance;
}

void MsgRegister::RegistPBRequestToMsgID(int32_t msgID, CMessageBody* (*func)())
{
    msgID_to_request_constructor[msgID] = func;
}

void MsgRegister::RegistPBResPonseToMsgID(int32_t msgID, CMessageBody* (*func)())
{
    msgID_to_response_constructor[msgID] = func;
}

CMessageBody* MsgRegister::NewRequestBody(int32_t msgID)
{
    if (msgID_to_request_constructor.find(msgID) == msgID_to_request_constructor.end())
    {
        return NULL;
    }
    return msgID_to_request_constructor[msgID]();
}

CMessageBody* MsgRegister::NewResponseBody(int32_t msgID)
{
    if (msgID_to_response_constructor.find(msgID) == msgID_to_response_constructor.end())
    {
        return NULL;
    }
    return msgID_to_response_constructor[msgID]();
}

NS_GJ_END
#pragma once
#ifndef __MESSAGE_REGISTER_H__
#define __MESSAGE_REGISTER_H__

#include "my/Common/Common_Head.h"
#include "my/Connect/CMessage.h"
using namespace std;

#define MSGREGISTER GameJoy::MsgRegister::Instance()

#define RegistPBToMessageID(MSGID, PB_REQ, PB_RES) \
    struct PBRegist_##PB_REQ_##PB_RES_##MSGID { \
        PBRegist_##PB_REQ_##PB_RES_##MSGID() { \
            MSGREGISTER->RegistPBRequestToMsgID(MSGID, GameJoy::CMessageBody::ConstructMessageBody<PB_REQ>); \
            MSGREGISTER->RegistPBResPonseToMsgID(MSGID, GameJoy::CMessageBody::ConstructMessageBody<PB_RES>); \
        } \
    }; \
    PBRegist_##PB_REQ_##PB_RES_##MSGID var_##PB_REQ_##PB_RES_##MSGID_##__LINE__;

#define NewRequestBodyWithMsgID(MSGID) MSGREGISTER->NewRequestBody(MSGID)
#define NewResponseBodtWithMsgID(MSGID) MSGREGISTER->NewResponseBody(MSGID) 

NS_GJ_BEGIN

class MsgRegister
{
public:
    static MsgRegister* Instance();
    void RegistPBRequestToMsgID(int32_t msgID, CMessageBody* (*func)());
    void RegistPBResPonseToMsgID(int32_t msgID, CMessageBody* (*func)());
    CMessageBody* NewRequestBody(int32_t msgID);
    CMessageBody* NewResponseBody(int32_t msgID);
private:
    MsgRegister() 
    { 
        msgID_to_request_constructor.clear(); 
        msgID_to_response_constructor.clear();
    }
    static MsgRegister* instance;
    map< int32_t, CMessageBody* (*)() > msgID_to_request_constructor;
    map< int32_t, CMessageBody* (*)() > msgID_to_response_constructor;
};


NS_GJ_END

#endif // !__MESSAGE_REGISTER_H__

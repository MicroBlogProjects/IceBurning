#pragma once
#ifndef __MESSAGE_REGISTER_H__
#define __MESSAGE_REGISTER_H__

#include "../Logicserver_Common.h"
#include "Logicserver_Message.h"

NS_LS_BEGIN

#define MSGREGISTER MsgRegister::Instance()

#define RegistPBToMessageID(MSGID, PB_REQ, PB_RES) \
    struct PBRegist##PB_REQ##PB_RES##MSGID { \
        PBRegist##PB_REQ##PB_RES##MSGID() { \
            MSGREGISTER->RegistPBRequestToMsgID(MSGID, NS_LS::CMessageBody::ConstructMessageBody<PB_REQ>); \
            MSGREGISTER->RegistPBResPonseToMsgID(MSGID, NS_LS::CMessageBody::ConstructMessageBody<PB_RES>); \
        } \
    }; \
    PBRegist##PB_REQ##PB_RES##MSGID var_PBRegist##PB_REQ##PB_RES##MSGID;

#define NewRequestBodyWithMsgID(MSGID) MSGREGISTER->NewRequestBody(MSGID)
#define NewResponseBodyWithMsgID(MSGID) MSGREGISTER->NewResponseBody(MSGID) 

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
    std::map< int32_t, CMessageBody* (*)() > msgID_to_request_constructor;
    std::map< int32_t, CMessageBody* (*)() > msgID_to_response_constructor;
};


NS_LS_END

#endif // !__MESSAGE_REGISTER_H__

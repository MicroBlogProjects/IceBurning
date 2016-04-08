#pragma once
#ifndef __MESSAGE_REGISTER_H__
#define __MESSAGE_REGISTER_H__

#include "Logicserver_Common.h"
#include "Logicserver_Message.h"
using namespace std;

#define RegistPBToMessageID(MSGID, PB_T) \
    struct PBRegist_##PB_T_##MSGID { \
        PBRegist_##PB_T_##MSGID() { \
            NS_LS::MsgRegister::Instance()->\
                RegistPBToMsgID(MSGID, NS_LS::CMessageBody::ConstructMessageBody<PB_T>); \
        } \
    }; \
    PBRegist_##PB_T_##MSGID LINE_##PB_T_##MSGID_##__LINE__;

#define NewMessageBodyWithMsgID(MSGID) NS_LS::MsgRegister::Instance()->NewMessageBody(MSGID)

NS_LS_BEGIN


class MsgRegister
{
public:
    static MsgRegister* Instance();
    void RegistPBToMsgID(int32_t msgID, CMessageBody* (*func)());
    CMessageBody* NewMessageBody(int32_t msgID);
private:
    MsgRegister() { msgID_to_constructor.clear(); }
    static MsgRegister* instance;
    map< int32_t, CMessageBody* (*)() > msgID_to_constructor;
};


NS_LS_END

#endif // !__MESSAGE_REGISTER_H__

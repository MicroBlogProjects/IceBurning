#pragma once
#ifndef __LOGICSERVER_FRAMEBASE_H__
#define __LOGICSERVER_FRAMEBASE_H__

#include "../Logicserver_Common.h"
#include "../Network/MessageRegister.h"
#include "../Network/Logicserver_Message.h"

NS_LS_BEGIN

#define GetFrameWithMsgID(msgID) CFrameRegister::Instance()->GetFrame(msgID)

#define RegistFrameWithMsgID(msgID, Frame)                                                  \
    struct Regist##Frame##msgID {                                                           \
        Regist##Frame##msgID() {                                                            \
            CFrameRegister::Instance()->RegistFrame(msgID, Frame::Instance());              \
        }                                                                                   \
    };                                                                                      \
    Regist##Frame##msgID var_Regist##Frame##msgID;

#define RegistFrameAndPBToMsgID(msgID, Frame, PBReq, PBRes)                                 \
    RegistFrameWithMsgID(msgID, Frame)                                                      \
    RegistPBToMessageID(msgID, PBReq, PBRes)


#define ProcessRequestBegin(msgID, PBREQ, PBRES)                                            \
    const PBREQ* pbReq = (PBREQ*)message.GetPB();                                           \
    CMessage msg_back;                                                                      \
    CMessageHead* head_back = new CMessageHead(message.GetUin(), msgID);                    \
    msg_back.SetMessageHead(head_back);                                                     \
    CMessageBody* body_back = NewResponseBodyWithMsgID(msgID);                              \
    if (body_back == NULL) {                                                                \
        TRACE_WARN("can not construct body with msgID(%d)", msgID);                         \
    }                                                                                       \
    PBRES* pbRes = (PBRES*)body_back->GetPB();

#define ProcessRequestEnd(res)                                                              \
    msg_back.SetMessageBody(body_back);                                                     \
    if (message.GetUin() < 0) {                                                             \
        head_back->SetMsq(message.GetMessageSequence());                                    \
    }                                                                                       \
    LOGICSOCKET->WriteOneMessage(msg_back);                                                 \
    return res;


class CFrameBase
{
public:
    virtual int32_t ProcessRequest(const CMessage& message) = 0;
};

class CFrameRegister
{
public:
    static CFrameRegister* Instance();

    int32_t RegistFrame(int32_t msgID, CFrameBase* frame);
    CFrameBase* GetFrame(int32_t msgID);
private:
    CFrameRegister() {}
private:
    static CFrameRegister* instance;
    std::map<int32_t, CFrameBase*> msgID_to_Frame;
};

NS_LS_END


#endif //__LOGICSERVER_FRAMEBASE_H__


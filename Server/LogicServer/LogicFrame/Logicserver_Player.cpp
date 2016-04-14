#include "Logicserver_Player.h"
#include "../Network/MessageRegister.h"

NS_LS_BEGIN

int32_t CPlayer::SendMessageToSelf(int32_t msgID, const CMessageBody& body) const
{
    CMessage msg;
    CMessageHead* h = new CMessageHead(uin, msgID);
    msg.SetMessageHead(h);
    CMessageBody* b = NewResponseBodyWithMsgID(msgID);
    b->GetPB()->CopyFrom(*(body.GetPB()));
    msg.SetMessageBody(b);
    return LOGICSOCKET->WriteOneMessage(msg);
}

NS_LS_END
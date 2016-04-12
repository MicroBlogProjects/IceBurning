#include "Logicserver_Player.h"

NS_LS_BEGIN

int32_t CPlayer::SendMessageToSelf(int32_t msgID, CMessageBody* body) const
{
    CMessage msg;
    CMessageHead* h = new CMessageHead(uin, msgID);
    msg.SetMessageHead(h);
    msg.SetMessageBody(body);

    return LOGICSOCKET->WriteOneMessage(msg);
}

NS_LS_END
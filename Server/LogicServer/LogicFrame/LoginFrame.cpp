#include "LoginFrame.h"
#include "../../Common/Console_Output.h"
#include "../Network/MessageRegister.h"
#include "../Network/Logicserver_Socket.h"
#include "../../Proto_out/Login.h"
#include "../../Proto_out/CreateRoom.h"


NS_LS_BEGIN

RegistFrameAndPBToMsgID(MSG_ON_LOGIN, CLoginFrame, CSLoginRequest, CSLoginResponse)
RegistFrameAndPBToMsgID(MSG_ON_PULL_ROOMS, CLoginFrame, CSPullRoomsRequest, CSPullRoomsResponse)
RegistFrameAndPBToMsgID(MSG_ON_CREATE_ROOM, CLoginFrame, CSCreateRoomRequest, CSCreateRoomResponse)
RegistFrameAndPBToMsgID(MSG_ON_JOIN_ROOM, CLoginFrame, CSJoinRoomRequest, CSJoinRoomResponse)
RegistFrameAndPBToMsgID(MSG_FIGHT_READY, CLoginFrame, CSFightReadyRequest, CSFightReadyResponse)

CLoginFrame* CLoginFrame::instance = NULL;

CLoginFrame* CLoginFrame::Instance()
{
    if (instance == NULL)
    {
        instance = new CLoginFrame();
    }
    return instance;
}

int32_t CLoginFrame::ProcessRequest(const CMessage& message)
{
    int32_t result = success;
    switch (message.GetMessageID())
    {
    case MSG_ON_LOGIN:
        result = ProcessRequestLogin(message);
        break;
    case MSG_ON_PULL_ROOMS:
        result = ProcessRequestPullRooms(message);
        break;
    case MSG_ON_CREATE_ROOM:
        result = ProcessRequestCreateRoom(message);
        break;
    case MSG_ON_JOIN_ROOM:
        result = ProcessRequestJoinRoom(message);
        break;
    case MSG_FIGHT_READY:
        result = ProcessRequestReadyFight(message);
        break;
    default:
        TRACE_WARN("can not find processor with msgID(%d)", message.GetMessageID());
        result = fail;
    }
    return result;
}

int32_t CLoginFrame::ProcessRequestLogin(const CMessage& message)
{
    console_msg("uin(%d) login", message.GetUin());
    ProcessRequestBegin(MSG_ON_LOGIN, CSLoginRequest, CSLoginResponse);
    if (pbReq)
    {
        console_msg("uin(%d), sq(%d)", message.GetUin(), message.GetMessageSequence());
    }
    else
    {
        console_msg("pb is null");
    }
    pbRes->set_uin(++uin_id_);
    pbRes->set_result(success);
    if (user == NULL)
    {
        user = new RoomMessage();
        user->uin = uin_id_;
        user->username = pbReq->username();
        ready_ = false;
    }
    ProcessRequestEnd(success);
}

int32_t CLoginFrame::ProcessRequestPullRooms(const CMessage& message)
{
    console_msg("uin(%d) PullRooms", message.GetUin());
    ProcessRequestBegin(MSG_ON_PULL_ROOMS, CSPullRoomsRequest, CSPullRoomsResponse);
    pbRes->set_result(fail);
    if (user != NULL && user->uin != message.GetUin() && hasRoom_)
    {
        pbRes->set_result(success);
        CSRoomMessage* r = pbRes->mutable_rooms();
        r->set_uin(user->uin);
        r->set_username(user->username);
    }
    ProcessRequestEnd(success);
}

int32_t CLoginFrame::ProcessRequestCreateRoom(const CMessage& message)
{
    console_msg("uin(%d) CreateRoom", message.GetUin());
    ProcessRequestBegin(MSG_ON_CREATE_ROOM, CSCreateRoomRequest, CSCreateRoomResponse);
    if (!hasRoom_)
    {
        hasRoom_ = 1;
    }
    user->uin = message.GetUin();
    pbRes->set_result(success);
    ProcessRequestEnd(success);
}
int32_t CLoginFrame::ProcessRequestJoinRoom(const CMessage& message)
{
    console_msg("uin(%d) JoinRoom", message.GetUin());
    ProcessRequestBegin(MSG_ON_JOIN_ROOM, CSJoinRoomRequest, CSJoinRoomResponse);
    if (user != NULL && user->uin == message.GetUin())
    {
        pbRes->set_result(fail);
    }
    else
    {
        CMessage msg;

        CMessageHead* h = new CMessageHead(user->uin, MSG_FIGHT_READY);
        msg.SetMessageHead(h);

        CMessageBody* b = NewResponseBodyWithMsgID(MSG_FIGHT_READY);
        CSJoinRoomResponse* pb = (CSJoinRoomResponse*)b->GetPB();
        pb->set_result(success);
        msg.SetMessageBody(b);

        LOGICSOCKET->WriteOneMessage(msg);


        pbRes->set_result(success);
    }
    ProcessRequestEnd(success);
}
int32_t CLoginFrame::ProcessRequestReadyFight(const CMessage& message)
{
    console_msg("uin(%d) ReadyFight", message.GetUin());
    ProcessRequestBegin(MSG_FIGHT_READY, CSFightReadyRequest, CSFightReadyResponse);
    if (user != NULL)
    {
        if (ready_)
        {
            CMessage msg;

            CMessageHead* h = new CMessageHead(user->uin, MSG_FIGHT_READY);
            msg.SetMessageHead(h);

            CMessageBody* b = NewResponseBodyWithMsgID(MSG_FIGHT_READY);
            CSFightReadyResponse* pb = (CSFightReadyResponse*)b->GetPB();
            pb->set_result(success);
            pbRes->set_result(success);
            msg.SetMessageBody(b);

            LOGICSOCKET->WriteOneMessage(msg);
            delete user;
            user = NULL;
            ready_ = 0;
            hasRoom_ = 0;
        }
        else
        {
            user->uin = message.GetUin();
            ready_ = 1;
        }
    }
    else
    {
        pbRes->set_result(fail);
    }
    ProcessRequestEnd(success);
}
NS_LS_END
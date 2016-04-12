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

int32_t RoomMessage::SIZE = 2;

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
    cur_uin_ = message.GetUin();
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
    if (message.GetUin() > 0 || players_.find(message.GetUin()) != players_.end())
    {
        pbRes->set_uin(-1);
        pbRes->set_result(fail);
    }
    else
    {
        pbRes->set_uin(++cnt_uin_);
        pbRes->set_result(success);
        OnPlayerLogin(CPlayer(cnt_uin_, pbReq->username(), pbReq->password()));
    }
    ProcessRequestEnd(success);
}

int32_t CLoginFrame::ProcessRequestPullRooms(const CMessage& message)
{
    console_msg("uin(%d) PullRooms", message.GetUin());
    ProcessRequestBegin(MSG_ON_PULL_ROOMS, CSPullRoomsRequest, CSPullRoomsResponse);
    pbRes->clear_rooms();
    for (std::map<int32_t, RoomMessage>::iterator it = rooms_.begin(); it != rooms_.end(); ++it)
    {
        CSRoomMessage* pbRoom = pbRes->add_rooms();
        const CPlayer& p = it->second.players_[0];
        pbRoom->set_uin(it->second.roomid_);
        pbRoom->set_username(p.GetUsername());
        console_msg("find a room with room ID(%d).", it->second.roomid_);
    }
    pbRes->set_result(success);
    ProcessRequestEnd(success);
}

int32_t CLoginFrame::ProcessRequestCreateRoom(const CMessage& message)
{
    console_msg("uin(%d) CreateRoom", message.GetUin());
    ProcessRequestBegin(MSG_ON_CREATE_ROOM, CSCreateRoomRequest, CSCreateRoomResponse);
    int32_t roomID = message.GetUin();
    if (rooms_.find(roomID) == rooms_.end())
    {
        RoomMessage room;
        room.isReady.clear();
        room.roomid_ = roomID;
        room.players_.push_back(players_[message.GetUin()]);
        rooms_[roomID] = room;
        pbRes->set_result(success);
    }
    else
    {
        pbRes->set_result(fail);
    }
    ProcessRequestEnd(success);
}
int32_t CLoginFrame::ProcessRequestJoinRoom(const CMessage& message)
{
    console_msg("uin(%d) JoinRoom", message.GetUin());
    ProcessRequestBegin(MSG_ON_JOIN_ROOM, CSJoinRoomRequest, CSJoinRoomResponse);
    int32_t roomID = pbReq->uin();
    if (rooms_.find(roomID) == rooms_.end())
    {
        pbRes->set_result(fail);
    }
    else
    {
        OnPlayerJoinRoom(roomID, players_[message.GetUin()]);
        pbRes->set_result(success);
    }
    ProcessRequestEnd(success);
}
int32_t CLoginFrame::ProcessRequestReadyFight(const CMessage& message)
{
    console_msg("uin(%d) ReadyFight", message.GetUin());
    ProcessRequestBegin(MSG_FIGHT_READY, CSFightReadyRequest, CSFightReadyResponse);
    int32_t roomID = -1;
    for (std::map<int32_t, RoomMessage>::iterator it = rooms_.begin(); it != rooms_.end(); ++it)
    {
        if (it->second.HasPlayer(message.GetUin()))
        {
            roomID = it->second.roomid_;
        }
    }
    if (rooms_[roomID].isReady.size() < RoomMessage::SIZE)
    {
        pbRes->set_result(false);
    }
    else
    {
        pbRes->set_result(success);
        OnAllPlayerReady(roomID);
    }
    ProcessRequestEnd(success);
}

bool RoomMessage::HasPlayer(int32_t uin)
{
    for (int32_t i = 0; i < players_.size(); i ++)
    {
        if (players_[i].GetUin() == uin)
        {
            return true;
        }
    }
    return false;
}

int32_t CLoginFrame::OnPlayerLogin(const CPlayer& player)
{
    players_[player.GetUin()] = player;
    return success;
}

int32_t CLoginFrame::OnPlayerJoinRoom(int32_t roomID, const CPlayer& player)
{
    RoomMessage& room = rooms_[roomID];
    room.players_.push_back(player);

    if (room.players_.size() == RoomMessage::SIZE)
    {
        CMessageBody* b = NewResponseBodyWithMsgID(MSG_ON_JOIN_ROOM);
        CSJoinRoomResponse* pb = (CSJoinRoomResponse*)b->GetPB();
        pb->set_result(success);
        for (int32_t i = 0; i < room.players_.size(); ++i)
        {
            if (room.players_[i].GetUin() != player.GetUin())
            {
                room.players_[i].SendMessageToSelf(MSG_ON_JOIN_ROOM, b);
            }
        }
    }
    return success;
}

int32_t CLoginFrame::OnAllPlayerReady(int32_t roomID)
{
    RoomMessage& room = rooms_[roomID];
    CMessageBody* body = NewResponseBodyWithMsgID(MSG_FIGHT_READY);
    CSFightReadyResponse* pb = (CSFightReadyResponse*)body->GetPB();
    pb->set_result(success);
    for (size_t i = 0; i < room.players_.size(); ++i)
    {
        if (room.players_[i].GetUin() != cur_uin_)
        {
            room.players_[i].SendMessageToSelf(MSG_FIGHT_READY, body);
        }
    }
}

NS_LS_END
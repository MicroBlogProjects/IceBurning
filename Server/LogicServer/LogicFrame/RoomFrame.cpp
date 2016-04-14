#include "RoomFrame.h"
#include "LoginFrame.h"
#include "SyncFrame.h"
#include "../../Proto_out/Login.h"
#include "../../Proto_out/CreateRoom.h"
#include "Logicserver_Player.h"


NS_LS_BEGIN

RegistFrameAndPBToMsgID(MSG_ON_PULL_ROOMS, CRoomFrame, CSPullRoomsRequest, CSPullRoomsResponse)
RegistFrameAndPBToMsgID(MSG_ON_CREATE_ROOM, CRoomFrame, CSCreateRoomRequest, CSCreateRoomResponse)
RegistFrameAndPBToMsgID(MSG_ON_JOIN_ROOM, CRoomFrame, CSJoinRoomRequest, CSJoinRoomResponse)
RegistFrameAndPBToMsgID(MSG_FIGHT_READY, CRoomFrame, CSFightReadyRequest, CSFightReadyResponse)

int32_t RoomMessage::SIZE = 2;
CRoomFrame* CRoomFrame::instance = NULL;

bool RoomMessage::HasPlayer(int32_t uin)
{
    for (int32_t i = 0; i < players_.size(); i++)
    {
        if (players_[i]->GetUin() == uin)
        {
            return true;
        }
    }
    return false;
}

CRoomFrame* CRoomFrame::Instance()
{
    if (instance == NULL)
    {
        instance = new CRoomFrame();
    }
    return instance;
}

int32_t CRoomFrame::ProcessRequest(const CMessage& message)
{
    int32_t result = success;
    switch (message.GetMessageID())
    {
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

int32_t CRoomFrame::ProcessRequestPullRooms(const CMessage& message)
{
    console_msg("uin(%d) PullRooms", message.GetUin());
    ProcessRequestBegin(MSG_ON_PULL_ROOMS, CSPullRoomsRequest, CSPullRoomsResponse);
    pbRes->clear_rooms();
    for (std::map<int32_t, RoomMessage>::iterator it = rooms_.begin(); it != rooms_.end(); ++it)
    {
        if (it->second.room_status_ != OnWaitingJoin)
        {
            continue;
        }
        CSRoomMessage* pbRoom = pbRes->add_rooms();
        pbRoom->set_uin(it->second.roomid_);
        pbRoom->set_username(it->second.room_name_);
        console_msg("find a room with room ID(%d).", it->second.roomid_);
    }
    pbRes->set_result(success);
    ProcessRequestEnd(success);
}

int32_t CRoomFrame::ProcessRequestCreateRoom(const CMessage& message)
{
    console_msg("uin(%d) CreateRoom", message.GetUin());
    ProcessRequestBegin(MSG_ON_CREATE_ROOM, CSCreateRoomRequest, CSCreateRoomResponse);
    int32_t roomID = message.GetUin();
    do {
        CPlayer* p = CLoginFrame::Instance()->GetPlayer(message.GetUin());
        if (p == NULL || IsAlreadyInRoom(message.GetUin()))
        {
            pbRes->set_result(fail);
            break;
        }

        RoomMessage room;
        room.isReady.clear();
        room.roomid_ = roomID;
        room.players_.push_back(p);
        room.room_name_ = p->GetUsername();
        room.room_status_ = OnWaitingJoin;

        rooms_[roomID] = room;
        p->SetRoomID(roomID);
        pbRes->set_result(success);
    } while (0);
    ProcessRequestEnd(success);
}
int32_t CRoomFrame::ProcessRequestJoinRoom(const CMessage& message)
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
        console_msg("uin(%d), join room(%d)", message.GetUin(), roomID);
        OnPlayerJoinRoom(roomID, message.GetUin());
        pbRes->set_result(success);
    }
    ProcessRequestEnd(success);
}
int32_t CRoomFrame::ProcessRequestReadyFight(const CMessage& message)
{
    console_msg("uin(%d) ReadyFight, ", message.GetUin());
    ProcessRequestBegin(MSG_FIGHT_READY, CSFightReadyRequest, CSFightReadyResponse);
    int32_t roomID = CLoginFrame::Instance()->GetPlayer(message.GetUin())->GetRoomID();
    rooms_[roomID].isReady.insert(message.GetUin());
    if (rooms_[roomID].isReady.size() < RoomMessage::SIZE)
    {
        pbRes->set_result(fail);
    }
    else
    {
        pbRes->set_result(success);
        OnAllPlayerReady(roomID, message.GetUin());
    }
    ProcessRequestEnd(success);
}

bool CRoomFrame::IsAlreadyInRoom(int uin)
{
    for (std::map<int32_t, RoomMessage>::iterator it = rooms_.begin(); it != rooms_.end(); ++it)
    {
        if (it->second.HasPlayer(uin))
        {
            return true;
        }
    }
    return false;
}
int32_t CRoomFrame::OnPlayerJoinRoom(int32_t roomID, int32_t uin)
{
    RoomMessage& room = rooms_[roomID];
    CPlayer* player = CLoginFrame::Instance()->GetPlayer(uin);
    player->SetRoomID(roomID);
    room.players_.push_back(player);
    console_msg("roomId(%d) size(%d)", roomID, room.players_.size());

    if (room.players_.size() == RoomMessage::SIZE)
    {
        CMessageBody* b = NewResponseBodyWithMsgID(MSG_ON_JOIN_ROOM);
        CSJoinRoomResponse* pb = (CSJoinRoomResponse*)b->GetPB();
        pb->set_result(success);
        for (int32_t i = 0; i < room.players_.size(); ++i)
        {
            if (room.players_[i]->GetUin() != player->GetUin())
            {
                room.players_[i]->SendMessageToSelf(MSG_ON_JOIN_ROOM, *b);
            }
        }
        delete b;
        room.room_status_ = OnWaitingStart;
    }
    return success;
}

int32_t CRoomFrame::OnAllPlayerReady(int32_t roomID, int32_t sender_uin)
{
    RoomMessage& room = rooms_[roomID];
    CMessageBody* body = NewResponseBodyWithMsgID(MSG_FIGHT_READY);
    CSFightReadyResponse* pb = (CSFightReadyResponse*)body->GetPB();
    pb->set_result(success);
    for (size_t i = 0; i < room.players_.size(); ++i)
    {
        if (room.players_[i]!= NULL && room.players_[i]->GetUin() != sender_uin)
        {
            room.players_[i]->SendMessageToSelf(MSG_FIGHT_READY, *body);
        }
    }
    delete body;
    room.room_status_ = OnPlaying;
    CSyncFrame::Instance()->OnNewRoomStartFight(roomID);
    return success;
}

int32_t CRoomFrame::GetRoomID(int uin)
{
    for (std::map<int32_t, RoomMessage>::iterator it = rooms_.begin(); it != rooms_.end(); ++it)
    {
        if (it->second.HasPlayer(uin))
        {
            return it->second.roomid_;
        }
    }
    return -1;
}

RoomMessage* CRoomFrame::GetRoomWithRoomID(int32_t roomID)
{
    if (rooms_.find(roomID) == rooms_.end())
    {
        return NULL;
    }
    return &rooms_[roomID];
}

NS_LS_END
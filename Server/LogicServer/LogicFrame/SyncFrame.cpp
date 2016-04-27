#include "SyncFrame.h"
#include "LoginFrame.h"
#include "RoomFrame.h"
#include "Logicserver_Player.h"

NS_LS_BEGIN

RegistFrameAndPBToMsgID(MSG_FRAME_SYNC, CSyncFrame, CSFrameSyncRequest, CSFrameSyncResponse)

CSyncFrame* CSyncFrame::instance = NULL;

CSyncFrame::CSyncFrame()
{
    
}

CSyncFrame* CSyncFrame::Instance()
{
    if (instance == NULL)
    {
        instance = new CSyncFrame();
    }
    return instance;
}

int32_t CSyncFrame::ProcessRequest(const CMessage& message)
{
    int32_t result = success;
    switch (message.GetMessageID())
    {
    case MSG_FRAME_SYNC:
        result = ProcessRequestRecvOneStep(message);
        break;
    default:
        TRACE_WARN("can not find processor with msgID(%d)", message.GetMessageID());
        result = fail;
    }
    return result;
}

int32_t CSyncFrame::ProcessRequestRecvOneStep(const CMessage& message)
{
    console_msg("uin(%d) sync frame", message.GetUin());
    ProcessRequestBegin(MSG_FRAME_SYNC, CSFrameSyncRequest, CSFrameSyncResponse);
    do
    {
        const CPlayer* player = CLoginFrame::Instance()->GetPlayer(message.GetUin());
        if (player == NULL)
        {
            TRACE_WARN("player not found in sync frame request");
            pbRes->set_result(fail);
            break;
        }
        int32_t roomID = player->GetRoomID();
        if (sync_frames_.find(roomID) == sync_frames_.end())
        {
            TRACE_WARN("uin(%d)'s room(%d) not existed when recv a sync frame", 
                message.GetUin(), player->GetRoomID());
            pbRes->set_result(fail);
            break;
        }
        std::vector<const PBFrameMessage*>& sync = sync_frames_[roomID];
        PBFrameMessage* sy_msg = new PBFrameMessage();
        sy_msg->CopyFrom(pbReq->step());
        sync.push_back(sy_msg);

        //pbRes->set_result(fail);
    } while (0);
    //ProcessRequestEnd(success)
}

int32_t CSyncFrame::OnNewRoomStartFight(int32_t roomID)
{
    sync_frames_[roomID] = std::vector<const PBFrameMessage*>();
    console_msg("a new room(%d) start fight", roomID);
    return success;
}
int32_t CSyncFrame::OnRoomFinishedFight(int32_t roomID)
{
    return success;
}

void CSyncFrame::OnOneFrameFinished()
{
    // 遍历每一个房间
    for (std::map<int32_t, std::vector<const PBFrameMessage*> >::iterator 
        it = sync_frames_.begin(); it != sync_frames_.end(); ++it)
    {
        // 这个房间没有帧信息
        /*if (it->second.size() <= 0)
        {
            continue;
        }*/
        console_msg("roomID(%d) has frame need sync", it->second.size());
        // 拿到房间信息
        const RoomMessage* room = CRoomFrame::Instance()->GetRoomWithRoomID(it->first);
        if (room == NULL || room->room_status_ != OnPlaying)
        {
            TRACE_WARN("room is null or status not right!");
            continue;
        }
        // 填充返回信息，包括帧序列
        const std::vector<const PBFrameMessage*>& sync = it->second;
        CMessageBody* msg_body = NewResponseBodyWithMsgID(MSG_FRAME_SYNC);
        CSFrameSyncResponse* pb = (CSFrameSyncResponse*)msg_body->GetPB();
        for (int i = 0; i < sync.size(); ++i)
        {
            PBFrameMessage* frame_msg = pb->add_steps();
            frame_msg->CopyFrom(*sync[i]);
        }
        pb->set_result(success);

        // 同时回复消息
        for (int i = 0; i < room->players_.size(); ++i)
        {
            room->players_[i]->SendMessageToSelf(MSG_FRAME_SYNC, *msg_body);
        }
        delete msg_body;
        // 清除这个房间的帧信息
        ClearSyncFrames(it->second);
    }
}

void CSyncFrame::ClearSyncFrames(std::vector<const PBFrameMessage*>& room)
{
    for (int i = 0; i < room.size(); ++i)
    {
        delete room[i];
    }
    room.clear();
}

NS_LS_END
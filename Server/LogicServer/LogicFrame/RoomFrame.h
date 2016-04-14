#pragma once
#ifndef __ROOM_FRAME_H__
#define __ROOM_FRAME_H__

#include "../Logicserver_Common.h"
#include "Logicserver_FrameBase.h"
#include "Logicserver_Player.h"

NS_LS_BEGIN

enum
{
    OnWaitingJoin = 1,
    OnWaitingStart = 2,
    OnPlaying = 3,
    OnFinished = 4,
};

struct RoomMessage
{
    static int32_t SIZE;
    int32_t roomid_;
    int32_t room_status_;
    std::string room_name_;
    std::vector<const CPlayer*> players_;
    std::set<int32_t> isReady;

    bool HasPlayer(int32_t uin);
};

class CRoomFrame : public CFrameBase
{
public:
    static CRoomFrame* Instance();
    virtual int32_t ProcessRequest(const CMessage& message);
    int32_t GetRoomID(int uin);
    RoomMessage* GetRoomWithRoomID(int32_t roomID);
private:
    CRoomFrame() {}

    int32_t ProcessRequestPullRooms(const CMessage& message);
    int32_t ProcessRequestCreateRoom(const CMessage& message);
    int32_t ProcessRequestJoinRoom(const CMessage& message);
    int32_t ProcessRequestReadyFight(const CMessage& message);

    bool IsAlreadyInRoom(int uin);
    int32_t OnPlayerJoinRoom(int32_t roomID, int32_t uin);
    int32_t OnAllPlayerReady(int32_t roomID, int32_t sender_uin);
private:
    static CRoomFrame* instance;
    std::map<int32_t, RoomMessage> rooms_;
};

NS_LS_END


#endif // !__ROOM_FRAME_H__

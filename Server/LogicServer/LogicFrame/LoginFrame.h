
#ifndef __LOGIN_FRAME_H__
#define __LOGIN_FRAME_H__

#include "../Logicserver_Common.h"
#include "../Network/Logicserver_Message.h"

#include "Logicserver_FrameBase.h"
#include "Logicserver_Player.h"

NS_LS_BEGIN

struct RoomMessage
{
    static int32_t SIZE;
    int32_t roomid_;
    std::vector<CPlayer> players_;
    std::set<int32_t> isReady;
    bool HasPlayer(int32_t uin);
};

class CLoginFrame : public CFrameBase
{
public:
    static CLoginFrame* Instance();
    virtual int32_t ProcessRequest(const CMessage& message);
private:
    CLoginFrame() { cnt_uin_ = 10000; }

    int32_t ProcessRequestLogin(const CMessage& message);
    int32_t ProcessRequestPullRooms(const CMessage& message);
    int32_t ProcessRequestCreateRoom(const CMessage& message);
    int32_t ProcessRequestJoinRoom(const CMessage& message);
    int32_t ProcessRequestReadyFight(const CMessage& message);

    int32_t OnPlayerLogin(const CPlayer& player);
    int32_t OnPlayerJoinRoom(int32_t roomID, const CPlayer& player);
    int32_t OnAllPlayerReady(int32_t roomID);

private: 
    static CLoginFrame* instance;

    int32_t cnt_uin_;
    int32_t cur_uin_;
    std::map<int32_t, CPlayer> players_;
    std::map<int32_t, RoomMessage> rooms_;
};

NS_LS_END

#endif // !__LOGIN_FRAME_H__
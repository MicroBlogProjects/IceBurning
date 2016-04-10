
#ifndef __LOGIN_FRAME_H__
#define __LOGIN_FRAME_H__

#include "../Logicserver_Common.h"
#include "Logicserver_FrameBase.h"
#include "../Network/Logicserver_Message.h"

NS_LS_BEGIN

struct RoomMessage
{
    int32_t uin;
    std::string username;
};

class CLoginFrame : public CFrameBase
{
public:
    static CLoginFrame* Instance();
    virtual int32_t ProcessRequest(const CMessage& message);
    void Ready() { ready_ = 1; }
private:
    CLoginFrame() { uin_id_ = 10000; user = NULL; ready_ = hasRoom_ = 0; }

    int32_t ProcessRequestLogin(const CMessage& message);
    int32_t ProcessRequestPullRooms(const CMessage& message);
    int32_t ProcessRequestCreateRoom(const CMessage& message);
    int32_t ProcessRequestJoinRoom(const CMessage& message);
    int32_t ProcessRequestReadyFight(const CMessage& message);

private: 
    static CLoginFrame* instance;
    int32_t uin_id_;
    RoomMessage* user;
    int ready_, hasRoom_;
};

NS_LS_END

#endif // !__LOGIN_FRAME_H__
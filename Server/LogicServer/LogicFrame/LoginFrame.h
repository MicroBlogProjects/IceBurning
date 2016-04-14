
#ifndef __LOGIN_FRAME_H__
#define __LOGIN_FRAME_H__

#include "../Logicserver_Common.h"
#include "../Network/Logicserver_Message.h"

#include "Logicserver_FrameBase.h"
#include "Logicserver_Player.h"

NS_LS_BEGIN

class CLoginFrame : public CFrameBase
{
public:
    static CLoginFrame* Instance();
    virtual int32_t ProcessRequest(const CMessage& message);
    CPlayer* GetPlayer(int32_t uin);
private:
    CLoginFrame() { cnt_uin_ = 10000; }
    int32_t ProcessRequestLogin(const CMessage& message);
    int32_t OnPlayerLogin(const CPlayer& player);

private: 
    static CLoginFrame* instance;

    int32_t cnt_uin_;
    std::map<int32_t, CPlayer*> players_;
};

NS_LS_END

#endif // !__LOGIN_FRAME_H__
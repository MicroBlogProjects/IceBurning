#pragma once
#ifndef __LOGICSERVER_LOGIC_FRAME_H__
#define __LOGICSERVER_LOGIC_FRAME_H__
#include "../Logicserver_Common.h"
#include "../Network/Logicserver_Message.h"
#include "../Network/Logicserver_Socket.h"

NS_LS_BEGIN

#define LOGICFRAME LogicFrame::Instance()

class LogicFrame
{
public:
    static LogicFrame* Instance();
    static int32_t HandleMessage();
    int32_t CheckTimer(struct timeval& now_time);

private:
    LogicFrame();
    int32_t HandleOneMessage(const CMessage* message);
    bool FinishOneFrame(struct timeval& now_time);
private:
    static LogicFrame* instance;
    struct timeval last_check_time_;
};

NS_LS_END

#endif // !__LOGICSERVER_LOGIC_FRAME_H__

#pragma once
#ifndef __LOGICSERVER_LOGIC_FRAME_H__
#define __LOGICSERVER_LOGIC_FRAME_H__
#include "Logicserver_Common.h"
#include "Logicserver_Socket.h"

NS_LS_BEGIN

#define LOGICFRAME LogicFrame::Instance()

class LogicFrame
{
public:
    static LogicFrame* Instance();
    static int32_t HandleMessage();

private:
    LogicFrame();
    int32_t HandleOneMessage(const CMessage* message);

private:
    static LogicFrame* instance;

};

NS_LS_END

#endif // !__LOGICSERVER_LOGIC_FRAME_H__

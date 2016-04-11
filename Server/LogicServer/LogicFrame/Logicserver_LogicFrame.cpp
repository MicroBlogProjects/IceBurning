#include "Logicserver_LogicFrame.h"
#include "Logicserver_FrameBase.h"
#include "LoginFrame.h"
#include "../Network/Logicserver_Socket.h"

NS_LS_BEGIN

LogicFrame* LogicFrame::instance = NULL;

LogicFrame::LogicFrame()
{
}

int32_t LogicFrame::HandleOneMessage(const CMessage* message)
{
    CFrameBase* frame = GetFrameWithMsgID(message->GetMessageID());
    frame->ProcessRequest(*message);
}

LogicFrame* LogicFrame::Instance()
{
    if (instance == NULL)
    {
        instance = new LogicFrame();
    }
    return instance;
}

int32_t LogicFrame::HandleMessage()
{
    std::vector<CMessage*> msgs;
    LOGICSOCKET->ReadMessages(msgs);
    for (size_t i = 0; i < msgs.size(); i++)
    {
        LOGICFRAME->HandleOneMessage(msgs[i]);
        delete msgs[i];
    }
}


NS_LS_END
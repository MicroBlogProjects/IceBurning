#include "Logicserver_LogicFrame.h"
#include "LoginFrame.h"
NS_LS_BEGIN

LogicFrame* LogicFrame::instance = NULL;

LogicFrame::LogicFrame()
{
}

int32_t LogicFrame::HandleOneMessage(const CMessage* message)
{
    CLoginFrame::Instance()->ProcessRequest(*message);
    //LOGICSOCKET->WriteOneMessage(*message);
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
    }
}


NS_LS_END
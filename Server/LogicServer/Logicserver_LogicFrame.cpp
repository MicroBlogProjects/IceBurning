#include "Logicserver_LogicFrame.h"

NS_LS_BEGIN

LogicFrame* LogicFrame::instance = NULL;

LogicFrame::LogicFrame()
{
}

int32_t LogicFrame::HandleOneMessage(const CMessage* message)
{
    // to do
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
  // to do 
}


NS_LS_END
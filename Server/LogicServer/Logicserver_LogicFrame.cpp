#include "Logicserver_LogicFrame.h"

NS_LS_BEGIN

LogicFrame* LogicFrame::instance = NULL;

LogicFrame::LogicFrame()
{
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

}


NS_LS_END
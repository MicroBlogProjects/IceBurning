#include "Logicserver_LogicFrame.h"
#include "Logicserver_FrameBase.h"
#include "LoginFrame.h"
#include "SyncFrame.h"

NS_LS_BEGIN

LogicFrame* LogicFrame::instance = NULL;

LogicFrame::LogicFrame()
{
    gettimeofday(&last_check_time_, NULL);
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
    int32_t ret = LOGICSOCKET->ReadMessages(msgs);
    if (ret == success)
    {
        for (size_t i = 0; i < msgs.size(); i++)
        {
            LOGICFRAME->HandleOneMessage(msgs[i]);
            delete msgs[i];
        }
    }
    else
    {
        TRACE_WARN("Connect server quit or error connect");
    }
    return ret;
}

int32_t LogicFrame::CheckTimer(struct timeval& now_time)
{
    if (!FinishOneFrame(now_time)) return fail;
    CSyncFrame::Instance()->OnOneFrameFinished();
    return success;
}

bool LogicFrame::FinishOneFrame(struct timeval& now_time)
{
    int32_t dis_ms = (now_time.tv_sec - last_check_time_.tv_sec) * 1000
        + (now_time.tv_usec - last_check_time_.tv_usec) / 1000;
    if (dis_ms * 6 < 100)
    {
        return false;
    }
    last_check_time_ = now_time;
    return true;
}


NS_LS_END


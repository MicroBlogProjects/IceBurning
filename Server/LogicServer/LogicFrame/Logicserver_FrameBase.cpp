#include "Logicserver_FrameBase.h"

NS_LS_BEGIN

CFrameRegister* CFrameRegister::instance = NULL;

CFrameRegister* CFrameRegister::Instance()
{
    if (instance == NULL)
    {
        instance = new CFrameRegister();
    }
    return instance;
}

int32_t CFrameRegister::RegistFrame(int32_t msgID, CFrameBase* frame)
{
    if (msgID_to_Frame.find(msgID) != msgID_to_Frame.end())
    {
        TRACE_WARN("regist the same msgID(%d) with different frame", msgID);
        return fail;
    }
    msgID_to_Frame[msgID] = frame;
    return success;
}

CFrameBase* CFrameRegister::GetFrame(int32_t msgID)
{
    return msgID_to_Frame[msgID];
}

NS_LS_END

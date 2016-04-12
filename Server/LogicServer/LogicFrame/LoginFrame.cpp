#include "LoginFrame.h"
#include "../../Common/Console_Output.h"
#include "../Network/MessageRegister.h"
#include "../Network/Logicserver_Socket.h"
#include "../../Proto_out/Login.h"


NS_LS_BEGIN

RegistFrameAndPBToMsgID(MSG_ON_LOGIN, CLoginFrame, CSLoginRequest, CSLoginResponse)

CLoginFrame* CLoginFrame::instance = NULL;

CLoginFrame* CLoginFrame::Instance()
{
    if (instance == NULL)
    {
        instance = new CLoginFrame();
    }
    return instance;
}

int32_t CLoginFrame::ProcessRequest(const CMessage& message)
{
    int32_t result = success;
    switch (message.GetMessageID())
    {
    case MSG_ON_LOGIN:
        result = ProcessRequestLogin(message);
        break;
    default:
        TRACE_WARN("can not find processor with msgID(%d)", message.GetMessageID());
        result = fail;
    }
    return result;
}

int32_t CLoginFrame::ProcessRequestLogin(const CMessage& message)
{
    console_msg("uin(%d) login", message.GetUin());
    ProcessRequestBegin(MSG_ON_LOGIN, CSLoginRequest, CSLoginResponse);
    if (message.GetUin() > 0 || players_.find(message.GetUin()) != players_.end())
    {
        pbRes->set_uin(-1);
        pbRes->set_result(fail);
        console_msg("login fail with uin(%d)", message.GetUin());
    }
    else
    {
        pbRes->set_uin(++cnt_uin_);
        pbRes->set_result(success);
        players_[cnt_uin_] = new CPlayer(cnt_uin_, pbReq->username(), pbReq->password());
        console_msg("login success with uin(%d)", message.GetUin());
    }
    ProcessRequestEnd(success);
}

int32_t CLoginFrame::OnPlayerLogin(const CPlayer& player)
{
    return success;
}

CPlayer* CLoginFrame::GetPlayer(int32_t uin)
{
    if (players_.find(uin) == players_.end())
    {
        return NULL;
    }
    return players_[uin];
}

NS_LS_END
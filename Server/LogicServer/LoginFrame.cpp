
#include "LoginFrame.h"
#include "../Proto_out/Login.h"
#include "../Common/Console_Output.h"
#include "MessageRegister.h"
#include "Logicserver_Socket.h"

NS_LS_BEGIN

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
    const CSLoginRequest* pb = (CSLoginRequest*) (message.GetPB());
    console_msg("username(%s), password(%s)", pb->username().c_str(), pb->password().c_str());

    CMessage msg;

    CMessageHead* msg_head = new CMessageHead(-1, MSG_ON_LOGIN);
    msg.SetMessageHead(msg_head);

    CMessageBody* msg_body = (CMessageBody*)NewResponseBodtWithMsgID(MSG_ON_LOGIN);
    CSLoginResponse* pb_back = (CSLoginResponse*)msg_body->GetPB();
    pb_back->set_uin(10000);
    pb_back->set_result(success);
    msg.SetMessageBody(msg_body);

    msg_head->SetMsq(message.GetMessageSequence());
    LOGICSOCKET->WriteOneMessage(msg);
    return success;
}

NS_LS_END
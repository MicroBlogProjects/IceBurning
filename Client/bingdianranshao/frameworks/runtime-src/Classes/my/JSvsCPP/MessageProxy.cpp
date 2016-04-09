#include "my/JSvsCPP/MessageProxy.h"

#include "my/Common/Common_Head.h"
#include "my/Connect/CMessage.h"
#include "my/Connect/ClientSocket.h"
#include "my/JSvsCPP/BindPBWithJS.h"
#include "google/protobuf/message.h"
#include "my/ProtoOut/MessageRegister.h"
#include "my/JSvsCPP/JS_CPP_Data_Exchange.h"

NS_GJ_BEGIN

MessageProxy* MessageProxy::instance = NULL;

MessageProxy* MessageProxy::Instance()
{
    if (instance == NULL)
    {
        instance = new MessageProxy();
    }
    return instance;
}

void MessageProxy::SendRequest(int msgID)
{
    JS_CPP_Bridge* js_obj = MSGIDBINDJSUNIT->GetJSRequestWithMsgID(msgID);
    if (js_obj == NULL)
    {
        CCLOG("can not find js obj with msgID(%d)", msgID);
        return ;
    }
    CMessage* msg = new CMessage();

    CMessageHead* msg_head = new CMessageHead();
    msg_head->SetMid(msgID);
    msg->SetMessageHead(msg_head);

    CMessageBody* msg_body = NewRequestBodyWithMsgID(msgID);
    FillPBWithJS(msgID, js_obj, msg_body->GetPB());
    msg->SetMessageBody(msg_body);

    //CLIENTSOCKET->SendDataToServer(msg);
    CLIENTSOCKET->push(msg);
}

int MessageProxy::RecvResponse()
{
    CMessage* msg= NULL;
    if (success == CLIENTSOCKET->RecvOneDataFromServer(msg) && msg)
    {
        JS_CPP_Bridge* js_obj = MSGIDBINDJSUNIT->getJSResponseWithMsgID(msg->GetMessageID());
        if (js_obj == NULL)
        {
            CCLOG("can not find js obj with msgID(%d)", msg->GetMessageID());
            return -1;
        }
        ::google::protobuf::Message* pb_obj = msg->GetPB();
        if (pb_obj == NULL)
        {
            CCLOG("get wrong pb obj when proxy recv response.");
            return -1;
        }
        FillJSWithPB(msg->GetMessageID(), pb_obj, js_obj);
        return msg->GetMessageID();
    }
    return -1;
}

NS_GJ_END
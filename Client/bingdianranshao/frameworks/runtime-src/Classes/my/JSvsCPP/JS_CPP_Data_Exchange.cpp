#include "JS_CPP_Data_Exchange.h"
#include "Message_i.h"

NS_GJ_BEGIN
MsgIdBindJSUnit* MsgIdBindJSUnit::instance = NULL;
MsgIdBindJSUnit* MsgIdBindJSUnit::Instance()
{
    if (instance == NULL)
    {
        instance = new MsgIdBindJSUnit();
    }
    return instance;
}
JS_CPP_Bridge* MsgIdBindJSUnit::GetJSRequestWithMsgID(int msgID)
{
    if (msgID_to_js_request.find(msgID) == msgID_to_js_request.end())
    {
        CCLOG("can not find js request obj with msgID(%d)", msgID);
        return NULL;
    }
    return msgID_to_js_request[msgID];
}
JS_CPP_Bridge* MsgIdBindJSUnit::getJSResponseWithMsgID(int msgID)
{
    if (msgID_to_js_response.find(msgID) == msgID_to_js_response.end())
    {
        CCLOG("can not find js response obj with msgID(%d)", msgID);
        return NULL;
    }
    return msgID_to_js_response[msgID];
}
void MsgIdBindJSUnit::BindMsgIDToJSRequest(int msgID, JS_CPP_Bridge* req)
{
    msgID_to_js_request[msgID] = req;
}
void MsgIdBindJSUnit::BindMsgIDToJSResponse(int msgID, JS_CPP_Bridge* res)
{
    msgID_to_js_response[msgID] = res;
}

/************************************************************************************/
// µÇÂ¼Ð­Òé
JS_CSLoginRequest* JS_CSLoginRequest::instance = NULL;
JS_CSLoginResponse* JS_CSLoginResponse::instance = NULL;

// to add 
JS_CSPullRoomsRequest* JS_CSPullRoomsRequest::instance = NULL;
JS_CSPullRoomsResponse* JS_CSPullRoomsResponse::instance = NULL;

//
JS_CSCreateRoomRequest* JS_CSCreateRoomRequest::instance = NULL;
JS_CSCreateRoomResponse* JS_CSCreateRoomResponse::instance = NULL;

//
JS_CSJoinRoomRequest* JS_CSJoinRoomRequest::instance = NULL;
JS_CSJoinRoomResponse* JS_CSJoinRoomResponse::instance = NULL;

//
JS_CSFightReadyRequest* JS_CSFightReadyRequest::instance = NULL;
JS_CSFightReadyResponse* JS_CSFightReadyResponse::instance = NULL;
/************************************************************************************/
NS_GJ_END
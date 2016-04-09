
#include "BindPBWithJS.h"
#include "Message_i.h"

#define ParseBegin(PB) \
    __try { \
        PB* real_pb = (PB*)pb; \
        GameJoy::JS_##PB * real_js = (GameJoy::JS_##PB *)js;

#define ParseEnd \
    } \
    __except(EXCEPTION_EXECUTE_HANDLER) { \
        return false; \
    } \
    return success;


/********************************************************************************************/
// 登录协议
#include "my/ProtoOut/Login.pb.h"
BindMsgIDToJSObj(MSG_ON_LOGIN, JS_CSLoginRequest, JS_CSLoginResponse)
BindParserJS_PB(MSG_ON_LOGIN, ParsePBResponseToJS_CSLogin, ParseJSToPBRequest_CSLogin)
int ParsePBResponseToJS_CSLogin(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js)
{
    ParseBegin(CSLoginResponse)
        real_js->result = real_pb->result();
        real_js->uin = real_pb->uin();
    ParseEnd
}
int ParseJSToPBRequest_CSLogin(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb)
{
    ParseBegin(CSLoginRequest)
        real_pb->set_username(real_js->username);
    real_pb->set_password(real_js->password);
    ParseEnd
}

// to add 下一个协议
/********************************************************************************************/


NS_GJ_BEGIN

BindTool* BindTool::instance = NULL;

BindTool* BindTool::Instance()
{
    if (instance == NULL)
    {
        instance = new BindTool();
    }
    return instance;
}

int BindTool::ParsePBToJS(int msgID, ::google::protobuf::Message* pb, JS_CPP_Bridge* js)
{
    if (msgID_to_PBParser.find(msgID) == msgID_to_PBParser.end())
    {
        console_msg("can not find PBPaser with msgID(%d)", msgID);
        return fail;
    }
    msgID_to_PBParser[msgID](pb, js);
    return success;
}

int BindTool::ParseJSToPB(int msgID, JS_CPP_Bridge* js, ::google::protobuf::Message* pb)
{
    if (msgID_to_JSParser.find(msgID) == msgID_to_JSParser.end())
    {
        console_msg("can not find jsparser with msgID(%d)", msgID);
        return fail;
    }
    msgID_to_JSParser[msgID](js, pb);
    return success;
}

void BindTool::BindMsgIDWithPBParser(int msgID, int(*func)(::google::protobuf::Message*, JS_CPP_Bridge*))
{
    if (msgID_to_PBParser.find(msgID) != msgID_to_PBParser.end())
    {
        console_msg("Bind msgID with PBParser error, msgID(%d) already Bind.", msgID);
        return;
    }
    msgID_to_PBParser[msgID] = func;
}

void BindTool::BindMsgIDWithJSParser(int msgID, int(*func)(JS_CPP_Bridge*, ::google::protobuf::Message*))
{
    if (msgID_to_JSParser.find(msgID) != msgID_to_JSParser.end())
    {
        console_msg("Bind msgID with JSParser error, msgID(%d) already Bind.", msgID);
        return;
    }
    msgID_to_JSParser[msgID] = func;
}


NS_GJ_END

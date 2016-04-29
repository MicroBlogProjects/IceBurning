
#include "my/JSvsCPP/BindPBWithJS.h"
#include "Message_i.h"
#include "my/JSvsCPP/MessageProxy.h"
#include "my/Common/Common_Tools.h"

#define ParseBegin(PB) \
    PB* real_pb = (PB*)pb; \
    GameJoy::JS_##PB * real_js = (GameJoy::JS_##PB *)js;

#define ParseEnd \
    return success;


/********************************************************************************************/
#include "my/ProtoOut/Login.pb.h"
// 登录协议
BindMsgIDToJSObj(MSG_ON_LOGIN, CSLoginRequest, CSLoginResponse)
BindParserJS_PB(MSG_ON_LOGIN, ParsePBResponseToJS_CSLogin, ParseJSToPBRequest_CSLogin)
// 拉取房间列表
BindMsgIDToJSObj(MSG_ON_PULL_ROOMS, CSPullRoomsRequest, CSPullRoomsResponse)
BindParserJS_PB(MSG_ON_PULL_ROOMS, ParsePBResponseToJS_CSPullRooms, ParseJSToPBRequest_CSPullRooms)

// 创建房间
#include "my/ProtoOut/CreateRoom.pb.h"
BindMsgIDToJSObj(MSG_ON_CREATE_ROOM, CSCreateRoomRequest, CSCreateRoomResponse)
BindParserJS_PB(MSG_ON_CREATE_ROOM, ParsePBResponseToJS_CSCreateRoom, ParseJSToPBRequest_CSCreateRoom)
// 加入房间
BindMsgIDToJSObj(MSG_ON_JOIN_ROOM, CSJoinRoomRequest, CSJoinRoomResponse)
BindParserJS_PB(MSG_ON_JOIN_ROOM, ParsePBResponseToJS_CSJoinRoom, ParseJSToPBRequest_CSJoinRoom)
// 准备就绪
BindMsgIDToJSObj(MSG_FIGHT_READY, CSFightReadyRequest, CSFightReadyResponse)
BindParserJS_PB(MSG_FIGHT_READY, ParsePBResponseToJS_CSFightReady, ParseJSToPBRequest_CSFightReady)


#include "my/ProtoOut/GamePlay.pb.h"
// 帧同步
BindMsgIDToJSObj(MSG_FRAME_SYNC, CSFrameSyncRequest, CSFrameSyncResponse)
BindParserJS_PB(MSG_FRAME_SYNC, ParsePBResponseToJS_CSFrameSync, ParseJSToPBRequest_CSFrameSync)
// 返回房间列表
BindMsgIDToJSObj(MSG_BACK_ROOM, CSBackRoomListRequest, CSBackRoomListResponse)
BindParserJS_PB(MSG_BACK_ROOM, ParsePBResponseToJS_CSBackRoom, ParseJSToPBRequest_CSBackRoom)

int ParsePBResponseToJS_CSLogin(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js)
{
    ParseBegin(CSLoginResponse)
        real_js->result = real_pb->result();
        real_js->uin = real_pb->uin();
		GameJoy::MessageProxy::Instance()->SetUin(real_js->uin);
    ParseEnd
}
int ParseJSToPBRequest_CSLogin(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb)
{
    ParseBegin(CSLoginRequest)
        real_pb->set_username(real_js->username);
        real_pb->set_password(real_js->password);
    ParseEnd
}

// 拉取房间列表
int ParsePBResponseToJS_CSPullRooms(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js)
{
	ParseBegin(CSPullRoomsResponse)
	(real_js->rooms).clear();
	for (int i = 0; i < real_pb->rooms_size(); ++i)
	{
		CSRoomMessage p = real_pb->rooms(i);
		GameJoy::JS_CSRoomMessage *t = new (GameJoy::JS_CSRoomMessage);
		t->set_uin(p.uin());
		t->set_username(p.username());
		(real_js->rooms).pushBack(t);
	}
	ParseEnd
}
int ParseJSToPBRequest_CSPullRooms(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb) 
{
	ParseBegin(CSPullRoomsRequest)
	ParseEnd
}

// 创建房间
int ParsePBResponseToJS_CSCreateRoom(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js)
{
	ParseBegin(CSCreateRoomResponse)
	real_js->result = real_pb->result();
	ParseEnd
}
int ParseJSToPBRequest_CSCreateRoom(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb)
{ 
	ParseBegin(CSCreateRoomRequest)
	ParseEnd
}
// 加入房间
int ParsePBResponseToJS_CSJoinRoom(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js)
{
	ParseBegin(CSJoinRoomResponse)
	real_js->result = real_pb->result();
	ParseEnd
}
int ParseJSToPBRequest_CSJoinRoom(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb)
{
	ParseBegin(CSJoinRoomRequest)
	real_pb->set_uin(real_js->uin);
	ParseEnd
}
// 准备就绪
int ParsePBResponseToJS_CSFightReady(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js)
{
	ParseBegin(CSFightReadyResponse)
	real_js->result = real_pb->result();
	ParseEnd
}
int ParseJSToPBRequest_CSFightReady(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb)
{
	ParseBegin(CSFightReadyRequest)
	ParseEnd
}


// 帧同步
int ParsePBResponseToJS_CSFrameSync(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js)
{
    ParseBegin(CSFrameSyncResponse);
    real_js->result = real_pb->result();

    cocos2d::Vector<GameJoy::JS_PBFrameMessage*>& js_steps = real_js->steps;
    char buf[MAX_CSMESSAGE_SIZE];
	js_steps.clear();
    for (int i = 0; i < real_pb->steps_size(); ++i)
    {
        const PBFrameMessage& pb_step = real_pb->steps(i);
        GameJoy::JS_PBFrameMessage* js_step = new GameJoy::JS_PBFrameMessage();

        char* str = buf;
        memcpy(str, pb_step.operation().c_str(), pb_step.operation().length());
        js_step->uin    = pb_step.uin();
        js_step->type   = DecodeInt32(str);
        js_step->obj_id = DecodeInt32(str);
        js_step->pos_x  = DecodeInt32(str);
        js_step->pos_y  = DecodeInt32(str);

        js_steps.pushBack(js_step);
    }
    ParseEnd
}
int ParseJSToPBRequest_CSFrameSync(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb)
{
    ParseBegin(CSFrameSyncRequest);
    PBFrameMessage* pb_step = real_pb->mutable_step();
    GameJoy::JS_PBFrameMessage* js_step = real_js->step;

    pb_step->set_uin(GameJoy::MessageProxy::GetUin());
    pb_step->set_uin(js_step->uin);
    char buf[MAX_CSMESSAGE_SIZE], *str = buf;
    memset(buf, 0, MAX_CSMESSAGE_SIZE);
	int len = 0;
    len += EncodeInt32(str, js_step->type);
	len += EncodeInt32(str, js_step->obj_id);
	len += EncodeInt32(str, js_step->pos_x);
	len += EncodeInt32(str, js_step->pos_y);
	std::string s(buf, len);
    pb_step->set_operation(s);
    ParseEnd
}

// 返回房间列表
int ParsePBResponseToJS_CSBackRoom(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js)
{
	ParseBegin(CSBackRoomListResponse)
	real_js->result = real_pb->result();
	ParseEnd
}
int ParseJSToPBRequest_CSBackRoom(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb)
{
	ParseBegin(CSBackRoomListRequest)
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
        CCLOG("can not find PBPaser with msgID(%d)", msgID);
        return fail;
    }
    msgID_to_PBParser[msgID](pb, js);
    return success;
}

int BindTool::ParseJSToPB(int msgID, JS_CPP_Bridge* js, ::google::protobuf::Message* pb)
{
    if (msgID_to_JSParser.find(msgID) == msgID_to_JSParser.end())
    {
        CCLOG("can not find jsparser with msgID(%d)", msgID);
        return fail;
    }
    msgID_to_JSParser[msgID](js, pb);
    return success;
}

void BindTool::BindMsgIDWithPBParser(int msgID, int(*func)(::google::protobuf::Message*, JS_CPP_Bridge*))
{
    if (msgID_to_PBParser.find(msgID) != msgID_to_PBParser.end())
    {
        CCLOG("Bind msgID with PBParser error, msgID(%d) already Bind.", msgID);
        return;
    }
    msgID_to_PBParser[msgID] = func;
}

void BindTool::BindMsgIDWithJSParser(int msgID, int(*func)(JS_CPP_Bridge*, ::google::protobuf::Message*))
{
    if (msgID_to_JSParser.find(msgID) != msgID_to_JSParser.end())
    {
        CCLOG("Bind msgID with JSParser error, msgID(%d) already Bind.", msgID);
        return;
    }
    msgID_to_JSParser[msgID] = func;
}


NS_GJ_END
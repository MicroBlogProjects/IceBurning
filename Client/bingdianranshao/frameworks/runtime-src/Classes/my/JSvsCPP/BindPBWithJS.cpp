
#include "BindPBWithJS.h"
#include "Message_i.h"

#define ParseBegin(PB) \
    PB* real_pb = (PB*)pb; \
    GameJoy::JS_##PB * real_js = (GameJoy::JS_##PB *)js;

#define ParseEnd \
    return success;


/********************************************************************************************/
// 登录协议
#include "my/ProtoOut/Login.pb.h"
BindMsgIDToJSObj(MSG_ON_LOGIN, CSLoginRequest, CSLoginResponse)
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

// 拉取房间列表
#include "my/ProtoOut/Login.pb.h"
BindMsgIDToJSObj(MSG_ON_PULL_ROOMS, CSPullRoomsRequest, CSPullRoomsResponse)
BindParserJS_PB(MSG_ON_PULL_ROOMS, ParsePBResponseToJS_CSPullRooms, ParseJSToPBRequest_CSPullRooms)
int ParsePBResponseToJS_CSPullRooms(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js)
{
	ParseBegin(CSPullRoomsResponse)
	real_js->result = real_pb->result();
    real_js->rooms = new GameJoy::JS_CSRoomMessage();
    real_js->rooms->uin = real_pb->rooms().uin();
    real_js->rooms->username = real_pb->rooms().username();
 //   real_js->rooms = new vector<GameJoy::JS_CSRoomMessage*>();
	//(real_js->rooms)->clear();
	//for (int i = 0; i < real_pb->rooms_size(); ++i)
	//{
	//	CSRoomMessage p = real_pb->rooms(i);
	//	GameJoy::JS_CSRoomMessage *t = new (GameJoy::JS_CSRoomMessage);
	//	t->set_uin(p.uin());
	//	t->set_username(p.username());
	//	(real_js->rooms)->push_back(t);
	//}
	ParseEnd
}
int ParseJSToPBRequest_CSPullRooms(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb) 
{
	ParseBegin(CSPullRoomsRequest)
	ParseEnd
}

// 创建房间
#include "my/ProtoOut/CreateRoom.pb.h"
BindMsgIDToJSObj(MSG_ON_CREATE_ROOM,CSCreateRoomRequest,CSCreateRoomResponse)
BindParserJS_PB(MSG_ON_CREATE_ROOM, ParsePBResponseToJS_CSCreateRoom, ParseJSToPBRequest_CSCreateRoom)
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
#include "my/ProtoOut/CreateRoom.pb.h"
BindMsgIDToJSObj(MSG_ON_JOIN_ROOM,CSJoinRoomRequest, CSJoinRoomResponse)
BindParserJS_PB(MSG_ON_JOIN_ROOM, ParsePBResponseToJS_CSJoinRoom, ParseJSToPBRequest_CSJoinRoom)
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
#include "my/ProtoOut/CreateRoom.pb.h"
BindMsgIDToJSObj(MSG_FIGHT_READY, CSFightReadyRequest, CSFightReadyResponse)
BindParserJS_PB(MSG_FIGHT_READY, ParsePBResponseToJS_CSFightReady, ParseJSToPBRequest_CSFightReady)
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

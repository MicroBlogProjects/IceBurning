#pragma once
#ifndef __BIND_JS_WITH_CPP_H__
#define __BIND_JS_WITH_CPP_H__

#include "my/Common/Common_Head.h"
#include "my/JSvsCPP/JS_CPP_Data_Exchange.h"
#include "google/protobuf/message.h"

#define BINDTOOL GameJoy::BindTool::Instance()

// 将一个js与一个pb相互转化，通过msgID作为标识
#define FillPBWithJS(msgID, js, pb) BINDTOOL->ParseJSToPB(msgID, js, pb)
#define FillJSWithPB(msgID, pb, js) BINDTOOL->ParsePBToJS(msgID, pb, js)

// 定义绑定（JS类）与(PB类)解析规则的宏，msgID这个id用下面两个函数实现相互转化
//      PBParser:将PB转为JS的函数，注意这时PB为Response
//      JSParser:将JS转为PB的函数，注意这时PB为Request
#define BindParserJS_PB(msgID, PBParser, JSParser) \
    struct Struct_##PBParser_##JSParser { \
        Struct_##PBParser_##JSParser() { \
            BINDTOOL->BindMsgIDWithPBParser(msgID, PBParser); \
            BINDTOOL->BindMsgIDWithJSParser(msgID, JSParser); \
        } \
    }; \
    struct Struct_##PBParser_##JSParser val_##PBParser_##JSParser;


/**************************************************************************************************/
// 登录模块
int ParsePBResponseToJS_CSLogin(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js);
int ParseJSToPBRequest_CSLogin(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb);
// 拉取房间列表
int ParsePBResponseToJS_CSPullRooms(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js);
int ParseJSToPBRequest_CSPullRooms(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb);
// 创建房间
int ParsePBResponseToJS_CSCreateRoom(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js);
int ParseJSToPBRequest_CSCreateRoom(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb);
// 加入房间
int ParsePBResponseToJS_CSJoinRoom(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js);
int ParseJSToPBRequest_CSJoinRoom(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb);
// 准备就绪
int ParsePBResponseToJS_CSFightReady(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js);
int ParseJSToPBRequest_CSFightReady(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb);

// 帧同步
int ParsePBResponseToJS_CSFrameSync(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js);
int ParseJSToPBRequest_CSFrameSync(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb);

// 返回房间列表
int ParsePBResponseToJS_CSBackRoom(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js);
int ParseJSToPBRequest_CSBackRoom(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb);

//to add
/**************************************************************************************************/

NS_GJ_BEGIN

class BindTool
{
public:
    static BindTool* Instance();
    int ParsePBToJS(int msgID, ::google::protobuf::Message* pb, JS_CPP_Bridge* js);
    int ParseJSToPB(int msgID, JS_CPP_Bridge* js, ::google::protobuf::Message* pb);
    void BindMsgIDWithPBParser(int msgID, int(*func)(::google::protobuf::Message*, JS_CPP_Bridge*));
    void BindMsgIDWithJSParser(int msgID, int(*func)(JS_CPP_Bridge*, ::google::protobuf::Message*));
private:
    BindTool() {}
private:
    static BindTool* instance;
    std::map<int, int(*)(::google::protobuf::Message*, JS_CPP_Bridge*) > msgID_to_PBParser;
    std::map<int, int(*)(JS_CPP_Bridge*, ::google::protobuf::Message*) > msgID_to_JSParser;
    std::map<int, JS_CPP_Bridge*> msgID_to_js;
};

NS_GJ_END

#endif // !__BIND_JS_WITH_CPP_H__
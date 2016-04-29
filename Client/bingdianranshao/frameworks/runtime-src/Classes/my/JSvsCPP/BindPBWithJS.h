#pragma once
#ifndef __BIND_JS_WITH_CPP_H__
#define __BIND_JS_WITH_CPP_H__

#include "my/Common/Common_Head.h"
#include "my/JSvsCPP/JS_CPP_Data_Exchange.h"
#include "google/protobuf/message.h"

#define BINDTOOL GameJoy::BindTool::Instance()

// ��һ��js��һ��pb�໥ת����ͨ��msgID��Ϊ��ʶ
#define FillPBWithJS(msgID, js, pb) BINDTOOL->ParseJSToPB(msgID, js, pb)
#define FillJSWithPB(msgID, pb, js) BINDTOOL->ParsePBToJS(msgID, pb, js)

// ����󶨣�JS�ࣩ��(PB��)��������ĺ꣬msgID���id��������������ʵ���໥ת��
//      PBParser:��PBתΪJS�ĺ�����ע����ʱPBΪResponse
//      JSParser:��JSתΪPB�ĺ�����ע����ʱPBΪRequest
#define BindParserJS_PB(msgID, PBParser, JSParser) \
    struct Struct_##PBParser_##JSParser { \
        Struct_##PBParser_##JSParser() { \
            BINDTOOL->BindMsgIDWithPBParser(msgID, PBParser); \
            BINDTOOL->BindMsgIDWithJSParser(msgID, JSParser); \
        } \
    }; \
    struct Struct_##PBParser_##JSParser val_##PBParser_##JSParser;


/**************************************************************************************************/
// ��¼ģ��
int ParsePBResponseToJS_CSLogin(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js);
int ParseJSToPBRequest_CSLogin(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb);
// ��ȡ�����б�
int ParsePBResponseToJS_CSPullRooms(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js);
int ParseJSToPBRequest_CSPullRooms(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb);
// ��������
int ParsePBResponseToJS_CSCreateRoom(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js);
int ParseJSToPBRequest_CSCreateRoom(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb);
// ���뷿��
int ParsePBResponseToJS_CSJoinRoom(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js);
int ParseJSToPBRequest_CSJoinRoom(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb);
// ׼������
int ParsePBResponseToJS_CSFightReady(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js);
int ParseJSToPBRequest_CSFightReady(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb);

// ֡ͬ��
int ParsePBResponseToJS_CSFrameSync(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js);
int ParseJSToPBRequest_CSFrameSync(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb);

// ���ط����б�
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
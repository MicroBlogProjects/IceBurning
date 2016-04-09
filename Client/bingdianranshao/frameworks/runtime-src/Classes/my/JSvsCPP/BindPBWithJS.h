#pragma once
#ifndef __BIND_JS_WITH_CPP_H__
#define __BIND_JS_WITH_CPP_H__

#include "my/Common/Common_Head.h"
#include "JS_CPP_Data_Exchange.h"
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
// MSG_ON_LOGIN : ��¼ģ��
int ParseJSToPBRequest_CSLogin(GameJoy::JS_CPP_Bridge* js, ::google::protobuf::Message* pb);
int ParsePBResponseToJS_CSLogin(::google::protobuf::Message* pb, GameJoy::JS_CPP_Bridge* js);
// to add
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

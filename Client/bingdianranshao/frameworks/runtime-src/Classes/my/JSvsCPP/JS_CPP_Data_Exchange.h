#ifndef __JS_CPP_DATA_EXCHANGE_H__ 
#define __JS_CPP_DATA_EXCHANGE_H__

#include <map>
#include "cocos2d.h"
#include "MessageProxy.h"
using namespace std;
#define NS_GJ_BEGIN     namespace GameJoy {
#define NS_GJ_END       }

// 定义绑定(msgId)与(js类)的宏
#define MSGIDBINDJSUNIT GameJoy::MsgIdBindJSUnit::Instance()
#define BindMsgIDToJSObj(msgID, JSReq, JSRes)                                                   \
    struct BindMsgIDToJsObj_##msgID_##JSReq_##JSRes {                                           \
        BindMsgIDToJsObj_##msgID_##JSReq_##JSRes() {                                            \
            MSGIDBINDJSUNIT->BindMsgIDToJSRequest(msgID, GameJoy::JS_##JSReq::Instance());      \
            MSGIDBINDJSUNIT->BindMsgIDToJSResponse(msgID, GameJoy::JS_##JSRes::Instance());     \
        }                                                                                       \
    };                                                                                          \
    BindMsgIDToJsObj_##msgID_##JSReq_##JSRes var_BindMsgIDToJsObj_##msgID_##JSReq_##JSRes;  

#define NewField(TYPE, NAME)                        \
	TYPE NAME;                                      \
	TYPE get_##NAME() { return NAME; }              \
	void set_##NAME(TYPE A##NAME) { NAME = A##NAME; }

#define NewRequest(PB)                                                              \
    class JS_##PB : public JS_CPP_Bridge {                                          \
    private:                                                                        \
        JS_##PB(int _msgID = -1) :msgID(_msgID) {}                                  \
    public:                                                                         \
        static JS_##PB* Instance(){                                                 \
            static JS_##PB* instance_##PB = new JS_##PB();                          \
            return instance_##PB;	                                                \
        }                                                                           \
        int msgID;                                                                  \
        int get_msgID() { return msgID; }                                           \
        void set_msgID(int _msgID) { msgID = _msgID; } 
#define EndRequest(PB)                                                              \
};                                                                              

#define NewResponse(PB)                                                             \
    class JS_##PB : public JS_CPP_Bridge {                                          \
    private:                                                                        \
        JS_##PB(int _result = 0):result(_result){}  \
    public:                                                                         \
        static JS_##PB* Instance(){                                                 \
            static JS_##PB* instance_##PB = new JS_##PB();                          \
            return instance_##PB;	                                                \
        }                                                                           \
        int result;                                                                 \
        int get_result() { return result; }                                         \
        void set_result(int _result) { result = _result; } 
#define EndResponse(PB)                                                             \
};

#define NewEntity(PB)                                        						\
	class JS_##PB : public JS_CPP_Bridge, public cocos2d::Ref{						\
	public:																			\
		JS_##PB() {}																\
		~JS_##PB(){}
#define EndEntity(PB)																\
};

NS_GJ_BEGIN

class Proxy
{
public:
    static void SendRequest(int msgID) { MessageProxy::Instance()->SendRequest(msgID); }
    static int RecvResponse() { return MessageProxy::Instance()->RecvResponse(); }
};

class JS_CPP_Bridge {
public:
    JS_CPP_Bridge() {}
    ~JS_CPP_Bridge() {}
};

class MsgIdBindJSUnit
{
public:
    static MsgIdBindJSUnit* Instance();
    void BindMsgIDToJSRequest(int msgID, JS_CPP_Bridge* req);
    void BindMsgIDToJSResponse(int msgID, JS_CPP_Bridge* res);
    JS_CPP_Bridge* GetJSRequestWithMsgID(int msgID);
    JS_CPP_Bridge* getJSResponseWithMsgID(int msgID);
private:
    MsgIdBindJSUnit() {}
    static MsgIdBindJSUnit* instance;

    std::map<int, JS_CPP_Bridge*> msgID_to_js_request;
    std::map<int, JS_CPP_Bridge*> msgID_to_js_response;
};

/******************************************************************************/
// 登录的协议
NewRequest(CSLoginRequest)
    NewField(string, username)
    NewField(string, password)
EndRequest(CSLoginRequest)
NewResponse(CSLoginResponse)
    NewField(int, uin)
EndResponse(CSLoginResponse)

// 拉取房间列表
NewEntity(CSRoomMessage)
    NewField(int, uin)
    NewField(string, username)
EndEntity(CSRoomMessage)
NewRequest(CSPullRoomsRequest)
EndRequest(CSPullRoomsRequest)
NewResponse(CSPullRoomsResponse)
    NewField(cocos2d::Vector<JS_CSRoomMessage*>, rooms)
EndResponse(CSPullRoomsResponse)

// 创建房间
NewRequest(CSCreateRoomRequest)
EndRequest(CSCreateRoomRequest)
NewResponse(CSCreateRoomResponse)
EndResponse(CSCreateRoomResponse)

// 请求加入房间
NewRequest(CSJoinRoomRequest)
    NewField(int, uin)
EndRequest(CSJoinRoomRequest)
NewResponse(CSJoinRoomResponse)
EndResponse(CSJoinRoomResponse)

// 准备就绪
NewRequest(CSFightReadyRequest)
EndRequest(CSFightReadyRequest)
NewResponse(CSFightReadyResponse)
EndResponse(CSFightReadyResponse)

// 帧同步信息
NewEntity(PBFrameMessage)
    NewField(int, uin)
    NewField(int, type)
    NewField(int, obj_id)
    NewField(int, pos_x)
    NewField(int, pos_y)
EndEntity(PBFrameMessage)
NewRequest(CSFrameSyncRequest)
    NewField(JS_PBFrameMessage*, step)
EndRequest(CSFrameSyncRequest)
NewResponse(CSFrameSyncResponse)
    NewField(cocos2d::Vector<JS_PBFrameMessage*>, steps)
EndResponse(CSFrameSyncResponse)

// to add 下一个协议
/******************************************************************************/



NS_GJ_END
#endif //!__JS_CPP_DATA_EXCHANGE_H__ 
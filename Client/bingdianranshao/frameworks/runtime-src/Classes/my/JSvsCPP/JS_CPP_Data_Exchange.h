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

#define NewField(TYPE, NAME) \
	TYPE NAME; \
	TYPE get_##NAME() { return NAME; } \
	void set_##NAME(TYPE A##NAME) { NAME = A##NAME; }
	
#define NewRequest(PB)                                                              \
    class JS_##PB : public JS_CPP_Bridge {                                          \
    private:                                                                        \
        JS_##PB(int _msgID = -1) :msgID(_msgID) {}                                  \
        static JS_##PB* instance;                                              		\
    public:                                                                         \
        static JS_##PB* Instance(){                                                 \
            if(instance == NULL) {                                             		\
                instance = new JS_##PB();                                      		\
            }                                                                       \
            return instance;	                                                    \
        }                                                                           \
        int msgID;                                                                  \
        int get_msgID() { return msgID; }                                           \
        void set_msgID(int _msgID) { msgID = _msgID; } 
#define EndRequest(PB)                                                              \
};                                                                              

#define NewResponse(PB)                                                             \
    class JS_##PB : public JS_CPP_Bridge {                                          \
    private:                                                                        \
        JS_##PB(int _msgID = -1, int _result = 0):msgID(_msgID), result(_result){}  \
        static JS_##PB* instance;                                              		\
    public:                                                                         \
        static JS_##PB* Instance() {                                                \
            if(instance == NULL) {                                             		\
                instance = new JS_##PB();                                     		\
            }                                                                       \
            return instance;                                                   		\
        }                                                                           \
                                                                                    \
        int msgID;                                                                  \
        int get_msgID() { return msgID; }                                           \
        void set_msgID(int _msgID) { msgID = _msgID; }                              \
                                                                                    \
        int result;                                                                 \
        int get_result() { return result; }                                         \
        void set_result(int _result) { result = _result; } 
#define EndResponse(PB)                                                             \
};

#define NewEntity(PB) 																\
	class JS_##PB : public JS_CPP_Bridge {											\
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

// to add 下一个协议
NewEntity(CSRoomMessage)
	NewField(int, uin)
	NewField(string, username)
EndEntity(CSRoomMessage)
NewRequest(CSPullRoomsRequest)
EndRequest(CSPullRoomsRequest)
NewResponse(CSPullRoomsResponse)
	NewField(JS_CSRoomMessage*, rooms)
EndResponse(CSPullRoomsResponse)

//
NewRequest(CSCreateRoomRequest)
EndRequest(CSCreateRoomRequest)
NewResponse(CSCreateRoomResponse)
EndResponse(CSCreateRoomResponse)

//
NewRequest(CSJoinRoomRequest)
  NewField(int,uin)
EndRequest(CSJoinRoomRequest)
NewResponse(CSJoinRoomResponse)
EndResponse(CSJoinRoomResponse)

//
NewRequest(CSFightReadyRequest)
EndRequest(CSFightReadyRequest)
NewResponse(CSFightReadyResponse)
EndResponse(CSFightReadyResponse)
/******************************************************************************/



NS_GJ_END
#endif //!__JS_CPP_DATA_EXCHANGE_H__ 
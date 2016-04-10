#ifndef __JS_CPP_DATA_EXCHANGE_H__ 
#define __JS_CPP_DATA_EXCHANGE_H__

#include <map>
#include "cocos2d.h"
#include "MessageProxy.h"

#define NS_GJ_BEGIN     namespace GameJoy {
#define NS_GJ_END       }

// 定义绑定(msgId)与(js类)的宏
#define MSGIDBINDJSUNIT GameJoy::MsgIdBindJSUnit::Instance()
#define BindMsgIDToJSObj(msgID, JSReq, JSRes)                                               \
    struct BindMsgIDToJsObj_##msgID_##JSReq_##JSRes {                                       \
        BindMsgIDToJsObj_##msgID_##JSReq_##JSRes() {                                        \
            MSGIDBINDJSUNIT->BindMsgIDToJSRequest(msgID, GameJoy::JSReq::Instance());       \
            MSGIDBINDJSUNIT->BindMsgIDToJSResponse(msgID, GameJoy::JSRes::Instance());      \
        }                                                                                   \
    };                                                                                      \
    BindMsgIDToJsObj_##msgID_##JSReq_##JSRes var_BindMsgIDToJsObj_##msgID_##JSReq_##JSRes;  


#define NewRequest(PB)                                                              \
    class JS_##PB : public JS_CPP_Bridge {                                          \
    private:                                                                        \
        JS_##PB(int _msgID = -1) :msgID(_msgID) {}                                  \
        static JS_##PB* instance_##PB;                                              \
    public:                                                                         \
        static JS_##PB* Instance(){                                                 \
            if(instance_##PB == NULL) {                                             \
                instance_##PB = new JS_##PB();                                      \
            }                                                                       \
            return instance_##PB;                                                   \
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
        static JS_##PB* instance_##PB;                                              \
    public:                                                                         \
        static JS_##PB* Instance() {                                                \
            if(instance_##PB == NULL) {                                             \
                instance_##PB = new JS_##PB();                                      \
            }                                                                       \
            return instance_##PB;                                                   \
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

    std::string username;
    std::string get_username() { return username; }
    void set_username(std::string _username) { username = _username; }

    std::string password;
    std::string get_password() { return password; }
    void set_password(std::string _password) { password = _password; }
EndRequest(CSLoginRequest)

NewResponse(CSLoginResponse)

    int uin;
    int get_uin() { return uin; }
    void set_uin(int _uin) { uin = _uin; }
EndResponse(CSLoginResponse)

// to add 下一个协议
/******************************************************************************/



NS_GJ_END
#endif //!__JS_CPP_DATA_EXCHANGE_H__ 
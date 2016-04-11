#include "base/ccConfig.h"
#ifndef __GameJoy_h__
#define __GameJoy_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_GameJoy_Proxy_class;
extern JSObject *jsb_GameJoy_Proxy_prototype;

bool js_GameJoy_Proxy_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_GameJoy_Proxy_finalize(JSContext *cx, JSObject *obj);
void js_register_GameJoy_Proxy(JSContext *cx, JS::HandleObject global);
void register_all_GameJoy(JSContext* cx, JS::HandleObject obj);
bool js_GameJoy_Proxy_RecvResponse(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_Proxy_SendRequest(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GameJoy_JS_CPP_Bridge_class;
extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

bool js_GameJoy_JS_CPP_Bridge_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_GameJoy_JS_CPP_Bridge_finalize(JSContext *cx, JSObject *obj);
void js_register_GameJoy_JS_CPP_Bridge(JSContext *cx, JS::HandleObject global);
void register_all_GameJoy(JSContext* cx, JS::HandleObject obj);
bool js_GameJoy_JS_CPP_Bridge_JS_CPP_Bridge(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GameJoy_JS_CSLoginRequest_class;
extern JSObject *jsb_GameJoy_JS_CSLoginRequest_prototype;

bool js_GameJoy_JS_CSLoginRequest_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_GameJoy_JS_CSLoginRequest_finalize(JSContext *cx, JSObject *obj);
void js_register_GameJoy_JS_CSLoginRequest(JSContext *cx, JS::HandleObject global);
void register_all_GameJoy(JSContext* cx, JS::HandleObject obj);
bool js_GameJoy_JS_CSLoginRequest_set_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSLoginRequest_set_username(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSLoginRequest_get_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSLoginRequest_get_username(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSLoginRequest_get_password(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSLoginRequest_set_password(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSLoginRequest_Instance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GameJoy_JS_CSLoginResponse_class;
extern JSObject *jsb_GameJoy_JS_CSLoginResponse_prototype;

bool js_GameJoy_JS_CSLoginResponse_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_GameJoy_JS_CSLoginResponse_finalize(JSContext *cx, JSObject *obj);
void js_register_GameJoy_JS_CSLoginResponse(JSContext *cx, JS::HandleObject global);
void register_all_GameJoy(JSContext* cx, JS::HandleObject obj);
bool js_GameJoy_JS_CSLoginResponse_get_result(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSLoginResponse_set_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSLoginResponse_get_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSLoginResponse_get_uin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSLoginResponse_set_result(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSLoginResponse_set_uin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSLoginResponse_Instance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GameJoy_JS_CSRoomMessage_class;
extern JSObject *jsb_GameJoy_JS_CSRoomMessage_prototype;

bool js_GameJoy_JS_CSRoomMessage_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_GameJoy_JS_CSRoomMessage_finalize(JSContext *cx, JSObject *obj);
void js_register_GameJoy_JS_CSRoomMessage(JSContext *cx, JS::HandleObject global);
void register_all_GameJoy(JSContext* cx, JS::HandleObject obj);
bool js_GameJoy_JS_CSRoomMessage_set_username(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSRoomMessage_set_uin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSRoomMessage_get_username(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSRoomMessage_get_uin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSRoomMessage_JS_CSRoomMessage(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GameJoy_JS_CSPullRoomsRequest_class;
extern JSObject *jsb_GameJoy_JS_CSPullRoomsRequest_prototype;

bool js_GameJoy_JS_CSPullRoomsRequest_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_GameJoy_JS_CSPullRoomsRequest_finalize(JSContext *cx, JSObject *obj);
void js_register_GameJoy_JS_CSPullRoomsRequest(JSContext *cx, JS::HandleObject global);
void register_all_GameJoy(JSContext* cx, JS::HandleObject obj);
bool js_GameJoy_JS_CSPullRoomsRequest_get_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSPullRoomsRequest_set_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSPullRoomsRequest_Instance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GameJoy_JS_CSPullRoomsResponse_class;
extern JSObject *jsb_GameJoy_JS_CSPullRoomsResponse_prototype;

bool js_GameJoy_JS_CSPullRoomsResponse_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_GameJoy_JS_CSPullRoomsResponse_finalize(JSContext *cx, JSObject *obj);
void js_register_GameJoy_JS_CSPullRoomsResponse(JSContext *cx, JS::HandleObject global);
void register_all_GameJoy(JSContext* cx, JS::HandleObject obj);
bool js_GameJoy_JS_CSPullRoomsResponse_get_result(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSPullRoomsResponse_set_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSPullRoomsResponse_get_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSPullRoomsResponse_set_result(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSPullRoomsResponse_set_rooms(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSPullRoomsResponse_get_rooms(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSPullRoomsResponse_Instance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GameJoy_JS_CSCreateRoomRequest_class;
extern JSObject *jsb_GameJoy_JS_CSCreateRoomRequest_prototype;

bool js_GameJoy_JS_CSCreateRoomRequest_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_GameJoy_JS_CSCreateRoomRequest_finalize(JSContext *cx, JSObject *obj);
void js_register_GameJoy_JS_CSCreateRoomRequest(JSContext *cx, JS::HandleObject global);
void register_all_GameJoy(JSContext* cx, JS::HandleObject obj);
bool js_GameJoy_JS_CSCreateRoomRequest_get_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSCreateRoomRequest_set_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSCreateRoomRequest_Instance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GameJoy_JS_CSCreateRoomResponse_class;
extern JSObject *jsb_GameJoy_JS_CSCreateRoomResponse_prototype;

bool js_GameJoy_JS_CSCreateRoomResponse_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_GameJoy_JS_CSCreateRoomResponse_finalize(JSContext *cx, JSObject *obj);
void js_register_GameJoy_JS_CSCreateRoomResponse(JSContext *cx, JS::HandleObject global);
void register_all_GameJoy(JSContext* cx, JS::HandleObject obj);
bool js_GameJoy_JS_CSCreateRoomResponse_get_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSCreateRoomResponse_get_result(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSCreateRoomResponse_set_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSCreateRoomResponse_set_result(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSCreateRoomResponse_Instance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GameJoy_JS_CSJoinRoomRequest_class;
extern JSObject *jsb_GameJoy_JS_CSJoinRoomRequest_prototype;

bool js_GameJoy_JS_CSJoinRoomRequest_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_GameJoy_JS_CSJoinRoomRequest_finalize(JSContext *cx, JSObject *obj);
void js_register_GameJoy_JS_CSJoinRoomRequest(JSContext *cx, JS::HandleObject global);
void register_all_GameJoy(JSContext* cx, JS::HandleObject obj);
bool js_GameJoy_JS_CSJoinRoomRequest_get_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSJoinRoomRequest_set_uin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSJoinRoomRequest_set_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSJoinRoomRequest_get_uin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSJoinRoomRequest_Instance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GameJoy_JS_CSJoinRoomResponse_class;
extern JSObject *jsb_GameJoy_JS_CSJoinRoomResponse_prototype;

bool js_GameJoy_JS_CSJoinRoomResponse_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_GameJoy_JS_CSJoinRoomResponse_finalize(JSContext *cx, JSObject *obj);
void js_register_GameJoy_JS_CSJoinRoomResponse(JSContext *cx, JS::HandleObject global);
void register_all_GameJoy(JSContext* cx, JS::HandleObject obj);
bool js_GameJoy_JS_CSJoinRoomResponse_get_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSJoinRoomResponse_get_result(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSJoinRoomResponse_set_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSJoinRoomResponse_set_result(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSJoinRoomResponse_Instance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GameJoy_JS_CSFightReadyRequest_class;
extern JSObject *jsb_GameJoy_JS_CSFightReadyRequest_prototype;

bool js_GameJoy_JS_CSFightReadyRequest_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_GameJoy_JS_CSFightReadyRequest_finalize(JSContext *cx, JSObject *obj);
void js_register_GameJoy_JS_CSFightReadyRequest(JSContext *cx, JS::HandleObject global);
void register_all_GameJoy(JSContext* cx, JS::HandleObject obj);
bool js_GameJoy_JS_CSFightReadyRequest_get_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSFightReadyRequest_set_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSFightReadyRequest_Instance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GameJoy_JS_CSFightReadyResponse_class;
extern JSObject *jsb_GameJoy_JS_CSFightReadyResponse_prototype;

bool js_GameJoy_JS_CSFightReadyResponse_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_GameJoy_JS_CSFightReadyResponse_finalize(JSContext *cx, JSObject *obj);
void js_register_GameJoy_JS_CSFightReadyResponse(JSContext *cx, JS::HandleObject global);
void register_all_GameJoy(JSContext* cx, JS::HandleObject obj);
bool js_GameJoy_JS_CSFightReadyResponse_get_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSFightReadyResponse_get_result(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSFightReadyResponse_set_msgID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSFightReadyResponse_set_result(JSContext *cx, uint32_t argc, jsval *vp);
bool js_GameJoy_JS_CSFightReadyResponse_Instance(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __GameJoy_h__

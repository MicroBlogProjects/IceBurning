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

#endif // __GameJoy_h__

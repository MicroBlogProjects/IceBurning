#include "jsb_GameJoy_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "JS_CPP_Data_Exchange.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_GameJoy_Proxy_class;
JSObject *jsb_GameJoy_Proxy_prototype;

bool js_GameJoy_Proxy_RecvResponse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        int ret = GameJoy::Proxy::RecvResponse();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_GameJoy_Proxy_RecvResponse : wrong number of arguments");
    return false;
}

bool js_GameJoy_Proxy_SendRequest(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_Proxy_SendRequest : Error processing arguments");
        GameJoy::Proxy::SendRequest(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_GameJoy_Proxy_SendRequest : wrong number of arguments");
    return false;
}


void js_register_GameJoy_Proxy(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_Proxy_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_Proxy_class->name = "Proxy";
    jsb_GameJoy_Proxy_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_Proxy_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_Proxy_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_Proxy_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_Proxy_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_Proxy_class->resolve = JS_ResolveStub;
    jsb_GameJoy_Proxy_class->convert = JS_ConvertStub;
    jsb_GameJoy_Proxy_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_Proxy_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("RecvResponse", js_GameJoy_Proxy_RecvResponse, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SendRequest", js_GameJoy_Proxy_SendRequest, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_GameJoy_Proxy_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_GameJoy_Proxy_class,
        dummy_constructor<GameJoy::Proxy>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_Proxy_prototype);
    jsb_register_class<GameJoy::Proxy>(cx, jsb_GameJoy_Proxy_class, proto, JS::NullPtr());
}

JSClass  *jsb_GameJoy_JS_CPP_Bridge_class;
JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

bool js_GameJoy_JS_CPP_Bridge_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    GameJoy::JS_CPP_Bridge* cobj = new (std::nothrow) GameJoy::JS_CPP_Bridge();

    js_type_class_t *typeClass = js_get_type_from_native<GameJoy::JS_CPP_Bridge>(cobj);

    // link the native object with the javascript object
    JS::RootedObject proto(cx, typeClass->proto.ref());
    JS::RootedObject parent(cx, typeClass->parentProto.ref());
    JS::RootedObject jsobj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    js_proxy_t* p = jsb_new_proxy(cobj, jsobj);
    AddNamedObjectRoot(cx, &p->obj, "GameJoy::JS_CPP_Bridge");
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_GameJoy_JS_CPP_Bridge_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    GameJoy::JS_CPP_Bridge *nobj = new (std::nothrow) GameJoy::JS_CPP_Bridge();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "GameJoy::JS_CPP_Bridge");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


void js_GameJoy_JS_CPP_Bridge_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (JS_CPP_Bridge)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject jsobj(cx, obj);
    jsproxy = jsb_get_js_proxy(jsobj);
    if (jsproxy) {
        GameJoy::JS_CPP_Bridge *nobj = static_cast<GameJoy::JS_CPP_Bridge *>(jsproxy->ptr);
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        if (nobj) {
            jsb_remove_proxy(nproxy, jsproxy);
            delete nobj;
        }
        else
            jsb_remove_proxy(nullptr, jsproxy);
    }
}
    
void js_register_GameJoy_JS_CPP_Bridge(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_CPP_Bridge_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_CPP_Bridge_class->name = "JS_CPP_Bridge";
    jsb_GameJoy_JS_CPP_Bridge_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CPP_Bridge_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_CPP_Bridge_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CPP_Bridge_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_CPP_Bridge_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_CPP_Bridge_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_CPP_Bridge_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_CPP_Bridge_class->finalize = js_GameJoy_JS_CPP_Bridge_finalize;
    jsb_GameJoy_JS_CPP_Bridge_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("ctor", js_GameJoy_JS_CPP_Bridge_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_GameJoy_JS_CPP_Bridge_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_GameJoy_JS_CPP_Bridge_class,
        js_GameJoy_JS_CPP_Bridge_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_register_class<GameJoy::JS_CPP_Bridge>(cx, jsb_GameJoy_JS_CPP_Bridge_class, proto, JS::NullPtr());
    anonEvaluate(cx, global, "(function () { GameJoy.JS_CPP_Bridge.extend = cc.Class.extend; })()");
}

JSClass  *jsb_GameJoy_JS_CSLoginRequest_class;
JSObject *jsb_GameJoy_JS_CSLoginRequest_prototype;

bool js_GameJoy_JS_CSLoginRequest_set_msgID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSLoginRequest* cobj = (GameJoy::JS_CSLoginRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSLoginRequest_set_msgID : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSLoginRequest_set_msgID : Error processing arguments");
        cobj->set_msgID(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSLoginRequest_set_msgID : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSLoginRequest_set_username(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSLoginRequest* cobj = (GameJoy::JS_CSLoginRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSLoginRequest_set_username : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSLoginRequest_set_username : Error processing arguments");
        cobj->set_username(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSLoginRequest_set_username : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSLoginRequest_get_msgID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSLoginRequest* cobj = (GameJoy::JS_CSLoginRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSLoginRequest_get_msgID : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_msgID();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSLoginRequest_get_msgID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSLoginRequest_get_username(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSLoginRequest* cobj = (GameJoy::JS_CSLoginRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSLoginRequest_get_username : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->get_username();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSLoginRequest_get_username : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSLoginRequest_get_password(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSLoginRequest* cobj = (GameJoy::JS_CSLoginRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSLoginRequest_get_password : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->get_password();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSLoginRequest_get_password : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSLoginRequest_set_password(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSLoginRequest* cobj = (GameJoy::JS_CSLoginRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSLoginRequest_set_password : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSLoginRequest_set_password : Error processing arguments");
        cobj->set_password(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSLoginRequest_set_password : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSLoginRequest_Instance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        GameJoy::JS_CSLoginRequest* ret = GameJoy::JS_CSLoginRequest::Instance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<GameJoy::JS_CSLoginRequest>(cx, (GameJoy::JS_CSLoginRequest*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_GameJoy_JS_CSLoginRequest_Instance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

void js_register_GameJoy_JS_CSLoginRequest(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_CSLoginRequest_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_CSLoginRequest_class->name = "JS_CSLoginRequest";
    jsb_GameJoy_JS_CSLoginRequest_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSLoginRequest_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_CSLoginRequest_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSLoginRequest_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_CSLoginRequest_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_CSLoginRequest_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_CSLoginRequest_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_CSLoginRequest_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_JS_CSLoginRequest_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("set_msgID", js_GameJoy_JS_CSLoginRequest_set_msgID, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_username", js_GameJoy_JS_CSLoginRequest_set_username, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_msgID", js_GameJoy_JS_CSLoginRequest_get_msgID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_username", js_GameJoy_JS_CSLoginRequest_get_username, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_password", js_GameJoy_JS_CSLoginRequest_get_password, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_password", js_GameJoy_JS_CSLoginRequest_set_password, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Instance", js_GameJoy_JS_CSLoginRequest_Instance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_GameJoy_JS_CSLoginRequest_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameJoy_JS_CSLoginRequest_class,
        dummy_constructor<GameJoy::JS_CSLoginRequest>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_CSLoginRequest_prototype);
    jsb_register_class<GameJoy::JS_CSLoginRequest>(cx, jsb_GameJoy_JS_CSLoginRequest_class, proto, parent_proto);
}

JSClass  *jsb_GameJoy_JS_CSLoginResponse_class;
JSObject *jsb_GameJoy_JS_CSLoginResponse_prototype;

bool js_GameJoy_JS_CSLoginResponse_set_uin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSLoginResponse* cobj = (GameJoy::JS_CSLoginResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSLoginResponse_set_uin : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSLoginResponse_set_uin : Error processing arguments");
        cobj->set_uin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSLoginResponse_set_uin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSLoginResponse_get_result(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSLoginResponse* cobj = (GameJoy::JS_CSLoginResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSLoginResponse_get_result : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_result();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSLoginResponse_get_result : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSLoginResponse_get_uin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSLoginResponse* cobj = (GameJoy::JS_CSLoginResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSLoginResponse_get_uin : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_uin();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSLoginResponse_get_uin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSLoginResponse_set_result(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSLoginResponse* cobj = (GameJoy::JS_CSLoginResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSLoginResponse_set_result : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSLoginResponse_set_result : Error processing arguments");
        cobj->set_result(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSLoginResponse_set_result : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSLoginResponse_Instance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        GameJoy::JS_CSLoginResponse* ret = GameJoy::JS_CSLoginResponse::Instance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<GameJoy::JS_CSLoginResponse>(cx, (GameJoy::JS_CSLoginResponse*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_GameJoy_JS_CSLoginResponse_Instance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

void js_register_GameJoy_JS_CSLoginResponse(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_CSLoginResponse_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_CSLoginResponse_class->name = "JS_CSLoginResponse";
    jsb_GameJoy_JS_CSLoginResponse_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSLoginResponse_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_CSLoginResponse_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSLoginResponse_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_CSLoginResponse_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_CSLoginResponse_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_CSLoginResponse_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_CSLoginResponse_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_JS_CSLoginResponse_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("set_uin", js_GameJoy_JS_CSLoginResponse_set_uin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_result", js_GameJoy_JS_CSLoginResponse_get_result, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_uin", js_GameJoy_JS_CSLoginResponse_get_uin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_result", js_GameJoy_JS_CSLoginResponse_set_result, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Instance", js_GameJoy_JS_CSLoginResponse_Instance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_GameJoy_JS_CSLoginResponse_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameJoy_JS_CSLoginResponse_class,
        dummy_constructor<GameJoy::JS_CSLoginResponse>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_CSLoginResponse_prototype);
    jsb_register_class<GameJoy::JS_CSLoginResponse>(cx, jsb_GameJoy_JS_CSLoginResponse_class, proto, parent_proto);
}

JSClass  *jsb_GameJoy_JS_CSRoomMessage_class;
JSObject *jsb_GameJoy_JS_CSRoomMessage_prototype;

bool js_GameJoy_JS_CSRoomMessage_set_username(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSRoomMessage* cobj = (GameJoy::JS_CSRoomMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSRoomMessage_set_username : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSRoomMessage_set_username : Error processing arguments");
        cobj->set_username(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSRoomMessage_set_username : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSRoomMessage_set_uin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSRoomMessage* cobj = (GameJoy::JS_CSRoomMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSRoomMessage_set_uin : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSRoomMessage_set_uin : Error processing arguments");
        cobj->set_uin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSRoomMessage_set_uin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSRoomMessage_get_username(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSRoomMessage* cobj = (GameJoy::JS_CSRoomMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSRoomMessage_get_username : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->get_username();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSRoomMessage_get_username : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSRoomMessage_get_uin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSRoomMessage* cobj = (GameJoy::JS_CSRoomMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSRoomMessage_get_uin : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_uin();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSRoomMessage_get_uin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSRoomMessage_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    GameJoy::JS_CSRoomMessage* cobj = new (std::nothrow) GameJoy::JS_CSRoomMessage();

    js_type_class_t *typeClass = js_get_type_from_native<GameJoy::JS_CSRoomMessage>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "GameJoy::JS_CSRoomMessage"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

void js_register_GameJoy_JS_CSRoomMessage(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_CSRoomMessage_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_CSRoomMessage_class->name = "JS_CSRoomMessage";
    jsb_GameJoy_JS_CSRoomMessage_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSRoomMessage_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_CSRoomMessage_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSRoomMessage_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_CSRoomMessage_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_CSRoomMessage_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_CSRoomMessage_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_CSRoomMessage_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_JS_CSRoomMessage_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("set_username", js_GameJoy_JS_CSRoomMessage_set_username, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_uin", js_GameJoy_JS_CSRoomMessage_set_uin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_username", js_GameJoy_JS_CSRoomMessage_get_username, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_uin", js_GameJoy_JS_CSRoomMessage_get_uin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    JS::RootedObject parent_proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_GameJoy_JS_CSRoomMessage_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameJoy_JS_CSRoomMessage_class,
        js_GameJoy_JS_CSRoomMessage_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_CSRoomMessage_prototype);
    jsb_register_class<GameJoy::JS_CSRoomMessage>(cx, jsb_GameJoy_JS_CSRoomMessage_class, proto, parent_proto);
}

JSClass  *jsb_GameJoy_JS_CSPullRoomsRequest_class;
JSObject *jsb_GameJoy_JS_CSPullRoomsRequest_prototype;

bool js_GameJoy_JS_CSPullRoomsRequest_get_msgID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSPullRoomsRequest* cobj = (GameJoy::JS_CSPullRoomsRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSPullRoomsRequest_get_msgID : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_msgID();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSPullRoomsRequest_get_msgID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSPullRoomsRequest_set_msgID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSPullRoomsRequest* cobj = (GameJoy::JS_CSPullRoomsRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSPullRoomsRequest_set_msgID : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSPullRoomsRequest_set_msgID : Error processing arguments");
        cobj->set_msgID(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSPullRoomsRequest_set_msgID : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSPullRoomsRequest_Instance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        GameJoy::JS_CSPullRoomsRequest* ret = GameJoy::JS_CSPullRoomsRequest::Instance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<GameJoy::JS_CSPullRoomsRequest>(cx, (GameJoy::JS_CSPullRoomsRequest*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_GameJoy_JS_CSPullRoomsRequest_Instance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

void js_register_GameJoy_JS_CSPullRoomsRequest(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_CSPullRoomsRequest_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_CSPullRoomsRequest_class->name = "JS_CSPullRoomsRequest";
    jsb_GameJoy_JS_CSPullRoomsRequest_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSPullRoomsRequest_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_CSPullRoomsRequest_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSPullRoomsRequest_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_CSPullRoomsRequest_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_CSPullRoomsRequest_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_CSPullRoomsRequest_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_CSPullRoomsRequest_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_JS_CSPullRoomsRequest_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("get_msgID", js_GameJoy_JS_CSPullRoomsRequest_get_msgID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_msgID", js_GameJoy_JS_CSPullRoomsRequest_set_msgID, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Instance", js_GameJoy_JS_CSPullRoomsRequest_Instance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_GameJoy_JS_CSPullRoomsRequest_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameJoy_JS_CSPullRoomsRequest_class,
        dummy_constructor<GameJoy::JS_CSPullRoomsRequest>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_CSPullRoomsRequest_prototype);
    jsb_register_class<GameJoy::JS_CSPullRoomsRequest>(cx, jsb_GameJoy_JS_CSPullRoomsRequest_class, proto, parent_proto);
}

JSClass  *jsb_GameJoy_JS_CSPullRoomsResponse_class;
JSObject *jsb_GameJoy_JS_CSPullRoomsResponse_prototype;

bool js_GameJoy_JS_CSPullRoomsResponse_set_rooms(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSPullRoomsResponse* cobj = (GameJoy::JS_CSPullRoomsResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSPullRoomsResponse_set_rooms : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vector<GameJoy::JS_CSRoomMessage *> arg0;
        ok &= jsval_to_ccvector(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSPullRoomsResponse_set_rooms : Error processing arguments");
        cobj->set_rooms(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSPullRoomsResponse_set_rooms : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSPullRoomsResponse_get_result(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSPullRoomsResponse* cobj = (GameJoy::JS_CSPullRoomsResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSPullRoomsResponse_get_result : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_result();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSPullRoomsResponse_get_result : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSPullRoomsResponse_get_rooms(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSPullRoomsResponse* cobj = (GameJoy::JS_CSPullRoomsResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSPullRoomsResponse_get_rooms : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<GameJoy::JS_CSRoomMessage *> ret = cobj->get_rooms();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSPullRoomsResponse_get_rooms : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSPullRoomsResponse_set_result(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSPullRoomsResponse* cobj = (GameJoy::JS_CSPullRoomsResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSPullRoomsResponse_set_result : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSPullRoomsResponse_set_result : Error processing arguments");
        cobj->set_result(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSPullRoomsResponse_set_result : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSPullRoomsResponse_Instance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        GameJoy::JS_CSPullRoomsResponse* ret = GameJoy::JS_CSPullRoomsResponse::Instance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<GameJoy::JS_CSPullRoomsResponse>(cx, (GameJoy::JS_CSPullRoomsResponse*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_GameJoy_JS_CSPullRoomsResponse_Instance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

void js_register_GameJoy_JS_CSPullRoomsResponse(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_CSPullRoomsResponse_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_CSPullRoomsResponse_class->name = "JS_CSPullRoomsResponse";
    jsb_GameJoy_JS_CSPullRoomsResponse_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSPullRoomsResponse_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_CSPullRoomsResponse_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSPullRoomsResponse_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_CSPullRoomsResponse_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_CSPullRoomsResponse_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_CSPullRoomsResponse_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_CSPullRoomsResponse_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_JS_CSPullRoomsResponse_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("set_rooms", js_GameJoy_JS_CSPullRoomsResponse_set_rooms, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_result", js_GameJoy_JS_CSPullRoomsResponse_get_result, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_rooms", js_GameJoy_JS_CSPullRoomsResponse_get_rooms, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_result", js_GameJoy_JS_CSPullRoomsResponse_set_result, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Instance", js_GameJoy_JS_CSPullRoomsResponse_Instance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_GameJoy_JS_CSPullRoomsResponse_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameJoy_JS_CSPullRoomsResponse_class,
        dummy_constructor<GameJoy::JS_CSPullRoomsResponse>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_CSPullRoomsResponse_prototype);
    jsb_register_class<GameJoy::JS_CSPullRoomsResponse>(cx, jsb_GameJoy_JS_CSPullRoomsResponse_class, proto, parent_proto);
}

JSClass  *jsb_GameJoy_JS_CSCreateRoomRequest_class;
JSObject *jsb_GameJoy_JS_CSCreateRoomRequest_prototype;

bool js_GameJoy_JS_CSCreateRoomRequest_get_msgID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSCreateRoomRequest* cobj = (GameJoy::JS_CSCreateRoomRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSCreateRoomRequest_get_msgID : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_msgID();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSCreateRoomRequest_get_msgID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSCreateRoomRequest_set_msgID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSCreateRoomRequest* cobj = (GameJoy::JS_CSCreateRoomRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSCreateRoomRequest_set_msgID : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSCreateRoomRequest_set_msgID : Error processing arguments");
        cobj->set_msgID(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSCreateRoomRequest_set_msgID : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSCreateRoomRequest_Instance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        GameJoy::JS_CSCreateRoomRequest* ret = GameJoy::JS_CSCreateRoomRequest::Instance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<GameJoy::JS_CSCreateRoomRequest>(cx, (GameJoy::JS_CSCreateRoomRequest*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_GameJoy_JS_CSCreateRoomRequest_Instance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

void js_register_GameJoy_JS_CSCreateRoomRequest(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_CSCreateRoomRequest_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_CSCreateRoomRequest_class->name = "JS_CSCreateRoomRequest";
    jsb_GameJoy_JS_CSCreateRoomRequest_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSCreateRoomRequest_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_CSCreateRoomRequest_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSCreateRoomRequest_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_CSCreateRoomRequest_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_CSCreateRoomRequest_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_CSCreateRoomRequest_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_CSCreateRoomRequest_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_JS_CSCreateRoomRequest_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("get_msgID", js_GameJoy_JS_CSCreateRoomRequest_get_msgID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_msgID", js_GameJoy_JS_CSCreateRoomRequest_set_msgID, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Instance", js_GameJoy_JS_CSCreateRoomRequest_Instance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_GameJoy_JS_CSCreateRoomRequest_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameJoy_JS_CSCreateRoomRequest_class,
        dummy_constructor<GameJoy::JS_CSCreateRoomRequest>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_CSCreateRoomRequest_prototype);
    jsb_register_class<GameJoy::JS_CSCreateRoomRequest>(cx, jsb_GameJoy_JS_CSCreateRoomRequest_class, proto, parent_proto);
}

JSClass  *jsb_GameJoy_JS_CSCreateRoomResponse_class;
JSObject *jsb_GameJoy_JS_CSCreateRoomResponse_prototype;

bool js_GameJoy_JS_CSCreateRoomResponse_get_result(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSCreateRoomResponse* cobj = (GameJoy::JS_CSCreateRoomResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSCreateRoomResponse_get_result : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_result();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSCreateRoomResponse_get_result : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSCreateRoomResponse_set_result(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSCreateRoomResponse* cobj = (GameJoy::JS_CSCreateRoomResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSCreateRoomResponse_set_result : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSCreateRoomResponse_set_result : Error processing arguments");
        cobj->set_result(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSCreateRoomResponse_set_result : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSCreateRoomResponse_Instance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        GameJoy::JS_CSCreateRoomResponse* ret = GameJoy::JS_CSCreateRoomResponse::Instance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<GameJoy::JS_CSCreateRoomResponse>(cx, (GameJoy::JS_CSCreateRoomResponse*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_GameJoy_JS_CSCreateRoomResponse_Instance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

void js_register_GameJoy_JS_CSCreateRoomResponse(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_CSCreateRoomResponse_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_CSCreateRoomResponse_class->name = "JS_CSCreateRoomResponse";
    jsb_GameJoy_JS_CSCreateRoomResponse_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSCreateRoomResponse_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_CSCreateRoomResponse_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSCreateRoomResponse_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_CSCreateRoomResponse_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_CSCreateRoomResponse_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_CSCreateRoomResponse_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_CSCreateRoomResponse_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_JS_CSCreateRoomResponse_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("get_result", js_GameJoy_JS_CSCreateRoomResponse_get_result, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_result", js_GameJoy_JS_CSCreateRoomResponse_set_result, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Instance", js_GameJoy_JS_CSCreateRoomResponse_Instance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_GameJoy_JS_CSCreateRoomResponse_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameJoy_JS_CSCreateRoomResponse_class,
        dummy_constructor<GameJoy::JS_CSCreateRoomResponse>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_CSCreateRoomResponse_prototype);
    jsb_register_class<GameJoy::JS_CSCreateRoomResponse>(cx, jsb_GameJoy_JS_CSCreateRoomResponse_class, proto, parent_proto);
}

JSClass  *jsb_GameJoy_JS_CSJoinRoomRequest_class;
JSObject *jsb_GameJoy_JS_CSJoinRoomRequest_prototype;

bool js_GameJoy_JS_CSJoinRoomRequest_get_msgID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSJoinRoomRequest* cobj = (GameJoy::JS_CSJoinRoomRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSJoinRoomRequest_get_msgID : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_msgID();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSJoinRoomRequest_get_msgID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSJoinRoomRequest_set_uin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSJoinRoomRequest* cobj = (GameJoy::JS_CSJoinRoomRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSJoinRoomRequest_set_uin : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSJoinRoomRequest_set_uin : Error processing arguments");
        cobj->set_uin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSJoinRoomRequest_set_uin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSJoinRoomRequest_set_msgID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSJoinRoomRequest* cobj = (GameJoy::JS_CSJoinRoomRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSJoinRoomRequest_set_msgID : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSJoinRoomRequest_set_msgID : Error processing arguments");
        cobj->set_msgID(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSJoinRoomRequest_set_msgID : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSJoinRoomRequest_get_uin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSJoinRoomRequest* cobj = (GameJoy::JS_CSJoinRoomRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSJoinRoomRequest_get_uin : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_uin();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSJoinRoomRequest_get_uin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSJoinRoomRequest_Instance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        GameJoy::JS_CSJoinRoomRequest* ret = GameJoy::JS_CSJoinRoomRequest::Instance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<GameJoy::JS_CSJoinRoomRequest>(cx, (GameJoy::JS_CSJoinRoomRequest*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_GameJoy_JS_CSJoinRoomRequest_Instance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

void js_register_GameJoy_JS_CSJoinRoomRequest(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_CSJoinRoomRequest_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_CSJoinRoomRequest_class->name = "JS_CSJoinRoomRequest";
    jsb_GameJoy_JS_CSJoinRoomRequest_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSJoinRoomRequest_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_CSJoinRoomRequest_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSJoinRoomRequest_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_CSJoinRoomRequest_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_CSJoinRoomRequest_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_CSJoinRoomRequest_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_CSJoinRoomRequest_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_JS_CSJoinRoomRequest_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("get_msgID", js_GameJoy_JS_CSJoinRoomRequest_get_msgID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_uin", js_GameJoy_JS_CSJoinRoomRequest_set_uin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_msgID", js_GameJoy_JS_CSJoinRoomRequest_set_msgID, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_uin", js_GameJoy_JS_CSJoinRoomRequest_get_uin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Instance", js_GameJoy_JS_CSJoinRoomRequest_Instance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_GameJoy_JS_CSJoinRoomRequest_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameJoy_JS_CSJoinRoomRequest_class,
        dummy_constructor<GameJoy::JS_CSJoinRoomRequest>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_CSJoinRoomRequest_prototype);
    jsb_register_class<GameJoy::JS_CSJoinRoomRequest>(cx, jsb_GameJoy_JS_CSJoinRoomRequest_class, proto, parent_proto);
}

JSClass  *jsb_GameJoy_JS_CSJoinRoomResponse_class;
JSObject *jsb_GameJoy_JS_CSJoinRoomResponse_prototype;

bool js_GameJoy_JS_CSJoinRoomResponse_get_result(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSJoinRoomResponse* cobj = (GameJoy::JS_CSJoinRoomResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSJoinRoomResponse_get_result : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_result();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSJoinRoomResponse_get_result : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSJoinRoomResponse_set_result(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSJoinRoomResponse* cobj = (GameJoy::JS_CSJoinRoomResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSJoinRoomResponse_set_result : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSJoinRoomResponse_set_result : Error processing arguments");
        cobj->set_result(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSJoinRoomResponse_set_result : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSJoinRoomResponse_Instance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        GameJoy::JS_CSJoinRoomResponse* ret = GameJoy::JS_CSJoinRoomResponse::Instance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<GameJoy::JS_CSJoinRoomResponse>(cx, (GameJoy::JS_CSJoinRoomResponse*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_GameJoy_JS_CSJoinRoomResponse_Instance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

void js_register_GameJoy_JS_CSJoinRoomResponse(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_CSJoinRoomResponse_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_CSJoinRoomResponse_class->name = "JS_CSJoinRoomResponse";
    jsb_GameJoy_JS_CSJoinRoomResponse_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSJoinRoomResponse_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_CSJoinRoomResponse_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSJoinRoomResponse_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_CSJoinRoomResponse_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_CSJoinRoomResponse_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_CSJoinRoomResponse_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_CSJoinRoomResponse_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_JS_CSJoinRoomResponse_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("get_result", js_GameJoy_JS_CSJoinRoomResponse_get_result, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_result", js_GameJoy_JS_CSJoinRoomResponse_set_result, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Instance", js_GameJoy_JS_CSJoinRoomResponse_Instance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_GameJoy_JS_CSJoinRoomResponse_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameJoy_JS_CSJoinRoomResponse_class,
        dummy_constructor<GameJoy::JS_CSJoinRoomResponse>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_CSJoinRoomResponse_prototype);
    jsb_register_class<GameJoy::JS_CSJoinRoomResponse>(cx, jsb_GameJoy_JS_CSJoinRoomResponse_class, proto, parent_proto);
}

JSClass  *jsb_GameJoy_JS_CSFightReadyRequest_class;
JSObject *jsb_GameJoy_JS_CSFightReadyRequest_prototype;

bool js_GameJoy_JS_CSFightReadyRequest_get_msgID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSFightReadyRequest* cobj = (GameJoy::JS_CSFightReadyRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSFightReadyRequest_get_msgID : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_msgID();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSFightReadyRequest_get_msgID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSFightReadyRequest_set_msgID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSFightReadyRequest* cobj = (GameJoy::JS_CSFightReadyRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSFightReadyRequest_set_msgID : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSFightReadyRequest_set_msgID : Error processing arguments");
        cobj->set_msgID(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSFightReadyRequest_set_msgID : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSFightReadyRequest_Instance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        GameJoy::JS_CSFightReadyRequest* ret = GameJoy::JS_CSFightReadyRequest::Instance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<GameJoy::JS_CSFightReadyRequest>(cx, (GameJoy::JS_CSFightReadyRequest*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_GameJoy_JS_CSFightReadyRequest_Instance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

void js_register_GameJoy_JS_CSFightReadyRequest(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_CSFightReadyRequest_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_CSFightReadyRequest_class->name = "JS_CSFightReadyRequest";
    jsb_GameJoy_JS_CSFightReadyRequest_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSFightReadyRequest_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_CSFightReadyRequest_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSFightReadyRequest_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_CSFightReadyRequest_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_CSFightReadyRequest_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_CSFightReadyRequest_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_CSFightReadyRequest_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_JS_CSFightReadyRequest_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("get_msgID", js_GameJoy_JS_CSFightReadyRequest_get_msgID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_msgID", js_GameJoy_JS_CSFightReadyRequest_set_msgID, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Instance", js_GameJoy_JS_CSFightReadyRequest_Instance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_GameJoy_JS_CSFightReadyRequest_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameJoy_JS_CSFightReadyRequest_class,
        dummy_constructor<GameJoy::JS_CSFightReadyRequest>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_CSFightReadyRequest_prototype);
    jsb_register_class<GameJoy::JS_CSFightReadyRequest>(cx, jsb_GameJoy_JS_CSFightReadyRequest_class, proto, parent_proto);
}

JSClass  *jsb_GameJoy_JS_CSFightReadyResponse_class;
JSObject *jsb_GameJoy_JS_CSFightReadyResponse_prototype;

bool js_GameJoy_JS_CSFightReadyResponse_get_result(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSFightReadyResponse* cobj = (GameJoy::JS_CSFightReadyResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSFightReadyResponse_get_result : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_result();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSFightReadyResponse_get_result : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSFightReadyResponse_set_result(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSFightReadyResponse* cobj = (GameJoy::JS_CSFightReadyResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSFightReadyResponse_set_result : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSFightReadyResponse_set_result : Error processing arguments");
        cobj->set_result(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSFightReadyResponse_set_result : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSFightReadyResponse_Instance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        GameJoy::JS_CSFightReadyResponse* ret = GameJoy::JS_CSFightReadyResponse::Instance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<GameJoy::JS_CSFightReadyResponse>(cx, (GameJoy::JS_CSFightReadyResponse*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_GameJoy_JS_CSFightReadyResponse_Instance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

void js_register_GameJoy_JS_CSFightReadyResponse(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_CSFightReadyResponse_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_CSFightReadyResponse_class->name = "JS_CSFightReadyResponse";
    jsb_GameJoy_JS_CSFightReadyResponse_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSFightReadyResponse_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_CSFightReadyResponse_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSFightReadyResponse_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_CSFightReadyResponse_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_CSFightReadyResponse_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_CSFightReadyResponse_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_CSFightReadyResponse_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_JS_CSFightReadyResponse_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("get_result", js_GameJoy_JS_CSFightReadyResponse_get_result, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_result", js_GameJoy_JS_CSFightReadyResponse_set_result, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Instance", js_GameJoy_JS_CSFightReadyResponse_Instance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_GameJoy_JS_CSFightReadyResponse_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameJoy_JS_CSFightReadyResponse_class,
        dummy_constructor<GameJoy::JS_CSFightReadyResponse>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_CSFightReadyResponse_prototype);
    jsb_register_class<GameJoy::JS_CSFightReadyResponse>(cx, jsb_GameJoy_JS_CSFightReadyResponse_class, proto, parent_proto);
}

JSClass  *jsb_GameJoy_JS_PBFrameMessage_class;
JSObject *jsb_GameJoy_JS_PBFrameMessage_prototype;

bool js_GameJoy_JS_PBFrameMessage_get_pos_y(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_PBFrameMessage* cobj = (GameJoy::JS_PBFrameMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_PBFrameMessage_get_pos_y : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_pos_y();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_PBFrameMessage_get_pos_y : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_PBFrameMessage_get_pos_x(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_PBFrameMessage* cobj = (GameJoy::JS_PBFrameMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_PBFrameMessage_get_pos_x : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_pos_x();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_PBFrameMessage_get_pos_x : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_PBFrameMessage_set_pos_y(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_PBFrameMessage* cobj = (GameJoy::JS_PBFrameMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_PBFrameMessage_set_pos_y : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_PBFrameMessage_set_pos_y : Error processing arguments");
        cobj->set_pos_y(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_PBFrameMessage_set_pos_y : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_PBFrameMessage_set_pos_x(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_PBFrameMessage* cobj = (GameJoy::JS_PBFrameMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_PBFrameMessage_set_pos_x : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_PBFrameMessage_set_pos_x : Error processing arguments");
        cobj->set_pos_x(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_PBFrameMessage_set_pos_x : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_PBFrameMessage_set_frame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_PBFrameMessage* cobj = (GameJoy::JS_PBFrameMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_PBFrameMessage_set_frame : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_PBFrameMessage_set_frame : Error processing arguments");
        cobj->set_frame(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_PBFrameMessage_set_frame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_PBFrameMessage_get_uin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_PBFrameMessage* cobj = (GameJoy::JS_PBFrameMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_PBFrameMessage_get_uin : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_uin();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_PBFrameMessage_get_uin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_PBFrameMessage_set_type(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_PBFrameMessage* cobj = (GameJoy::JS_PBFrameMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_PBFrameMessage_set_type : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_PBFrameMessage_set_type : Error processing arguments");
        cobj->set_type(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_PBFrameMessage_set_type : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_PBFrameMessage_get_obj_id(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_PBFrameMessage* cobj = (GameJoy::JS_PBFrameMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_PBFrameMessage_get_obj_id : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_obj_id();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_PBFrameMessage_get_obj_id : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_PBFrameMessage_get_type(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_PBFrameMessage* cobj = (GameJoy::JS_PBFrameMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_PBFrameMessage_get_type : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_type();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_PBFrameMessage_get_type : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_PBFrameMessage_set_obj_id(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_PBFrameMessage* cobj = (GameJoy::JS_PBFrameMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_PBFrameMessage_set_obj_id : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_PBFrameMessage_set_obj_id : Error processing arguments");
        cobj->set_obj_id(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_PBFrameMessage_set_obj_id : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_PBFrameMessage_set_uin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_PBFrameMessage* cobj = (GameJoy::JS_PBFrameMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_PBFrameMessage_set_uin : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_PBFrameMessage_set_uin : Error processing arguments");
        cobj->set_uin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_PBFrameMessage_set_uin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_PBFrameMessage_get_frame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_PBFrameMessage* cobj = (GameJoy::JS_PBFrameMessage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_PBFrameMessage_get_frame : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_frame();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_PBFrameMessage_get_frame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_PBFrameMessage_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    GameJoy::JS_PBFrameMessage* cobj = new (std::nothrow) GameJoy::JS_PBFrameMessage();

    js_type_class_t *typeClass = js_get_type_from_native<GameJoy::JS_PBFrameMessage>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "GameJoy::JS_PBFrameMessage"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

void js_register_GameJoy_JS_PBFrameMessage(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_PBFrameMessage_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_PBFrameMessage_class->name = "JS_PBFrameMessage";
    jsb_GameJoy_JS_PBFrameMessage_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_PBFrameMessage_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_PBFrameMessage_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_PBFrameMessage_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_PBFrameMessage_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_PBFrameMessage_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_PBFrameMessage_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_PBFrameMessage_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_JS_PBFrameMessage_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("get_pos_y", js_GameJoy_JS_PBFrameMessage_get_pos_y, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_pos_x", js_GameJoy_JS_PBFrameMessage_get_pos_x, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_pos_y", js_GameJoy_JS_PBFrameMessage_set_pos_y, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_pos_x", js_GameJoy_JS_PBFrameMessage_set_pos_x, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_frame", js_GameJoy_JS_PBFrameMessage_set_frame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_uin", js_GameJoy_JS_PBFrameMessage_get_uin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_type", js_GameJoy_JS_PBFrameMessage_set_type, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_obj_id", js_GameJoy_JS_PBFrameMessage_get_obj_id, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_type", js_GameJoy_JS_PBFrameMessage_get_type, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_obj_id", js_GameJoy_JS_PBFrameMessage_set_obj_id, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_uin", js_GameJoy_JS_PBFrameMessage_set_uin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_frame", js_GameJoy_JS_PBFrameMessage_get_frame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    JS::RootedObject parent_proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_GameJoy_JS_PBFrameMessage_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameJoy_JS_PBFrameMessage_class,
        js_GameJoy_JS_PBFrameMessage_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_PBFrameMessage_prototype);
    jsb_register_class<GameJoy::JS_PBFrameMessage>(cx, jsb_GameJoy_JS_PBFrameMessage_class, proto, parent_proto);
}

JSClass  *jsb_GameJoy_JS_CSFrameSyncRequest_class;
JSObject *jsb_GameJoy_JS_CSFrameSyncRequest_prototype;

bool js_GameJoy_JS_CSFrameSyncRequest_get_msgID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSFrameSyncRequest* cobj = (GameJoy::JS_CSFrameSyncRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSFrameSyncRequest_get_msgID : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_msgID();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSFrameSyncRequest_get_msgID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSFrameSyncRequest_get_step(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSFrameSyncRequest* cobj = (GameJoy::JS_CSFrameSyncRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSFrameSyncRequest_get_step : Invalid Native Object");
    if (argc == 0) {
        GameJoy::JS_PBFrameMessage* ret = cobj->get_step();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<GameJoy::JS_PBFrameMessage>(cx, (GameJoy::JS_PBFrameMessage*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSFrameSyncRequest_get_step : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSFrameSyncRequest_set_msgID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSFrameSyncRequest* cobj = (GameJoy::JS_CSFrameSyncRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSFrameSyncRequest_set_msgID : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSFrameSyncRequest_set_msgID : Error processing arguments");
        cobj->set_msgID(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSFrameSyncRequest_set_msgID : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSFrameSyncRequest_set_step(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSFrameSyncRequest* cobj = (GameJoy::JS_CSFrameSyncRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSFrameSyncRequest_set_step : Invalid Native Object");
    if (argc == 1) {
        GameJoy::JS_PBFrameMessage* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (GameJoy::JS_PBFrameMessage*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSFrameSyncRequest_set_step : Error processing arguments");
        cobj->set_step(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSFrameSyncRequest_set_step : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSFrameSyncRequest_Instance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        GameJoy::JS_CSFrameSyncRequest* ret = GameJoy::JS_CSFrameSyncRequest::Instance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<GameJoy::JS_CSFrameSyncRequest>(cx, (GameJoy::JS_CSFrameSyncRequest*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_GameJoy_JS_CSFrameSyncRequest_Instance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

void js_register_GameJoy_JS_CSFrameSyncRequest(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_CSFrameSyncRequest_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_CSFrameSyncRequest_class->name = "JS_CSFrameSyncRequest";
    jsb_GameJoy_JS_CSFrameSyncRequest_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSFrameSyncRequest_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_CSFrameSyncRequest_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSFrameSyncRequest_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_CSFrameSyncRequest_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_CSFrameSyncRequest_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_CSFrameSyncRequest_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_CSFrameSyncRequest_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_JS_CSFrameSyncRequest_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("get_msgID", js_GameJoy_JS_CSFrameSyncRequest_get_msgID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_step", js_GameJoy_JS_CSFrameSyncRequest_get_step, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_msgID", js_GameJoy_JS_CSFrameSyncRequest_set_msgID, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_step", js_GameJoy_JS_CSFrameSyncRequest_set_step, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Instance", js_GameJoy_JS_CSFrameSyncRequest_Instance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_GameJoy_JS_CSFrameSyncRequest_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameJoy_JS_CSFrameSyncRequest_class,
        dummy_constructor<GameJoy::JS_CSFrameSyncRequest>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_CSFrameSyncRequest_prototype);
    jsb_register_class<GameJoy::JS_CSFrameSyncRequest>(cx, jsb_GameJoy_JS_CSFrameSyncRequest_class, proto, parent_proto);
}

JSClass  *jsb_GameJoy_JS_CSFrameSyncResponse_class;
JSObject *jsb_GameJoy_JS_CSFrameSyncResponse_prototype;

bool js_GameJoy_JS_CSFrameSyncResponse_get_steps(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSFrameSyncResponse* cobj = (GameJoy::JS_CSFrameSyncResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSFrameSyncResponse_get_steps : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<GameJoy::JS_PBFrameMessage *> ret = cobj->get_steps();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSFrameSyncResponse_get_steps : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSFrameSyncResponse_get_result(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSFrameSyncResponse* cobj = (GameJoy::JS_CSFrameSyncResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSFrameSyncResponse_get_result : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_result();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSFrameSyncResponse_get_result : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_GameJoy_JS_CSFrameSyncResponse_set_steps(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSFrameSyncResponse* cobj = (GameJoy::JS_CSFrameSyncResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSFrameSyncResponse_set_steps : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vector<GameJoy::JS_PBFrameMessage *> arg0;
        ok &= jsval_to_ccvector(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSFrameSyncResponse_set_steps : Error processing arguments");
        cobj->set_steps(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSFrameSyncResponse_set_steps : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSFrameSyncResponse_set_result(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSFrameSyncResponse* cobj = (GameJoy::JS_CSFrameSyncResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSFrameSyncResponse_set_result : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSFrameSyncResponse_set_result : Error processing arguments");
        cobj->set_result(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSFrameSyncResponse_set_result : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSFrameSyncResponse_Instance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        GameJoy::JS_CSFrameSyncResponse* ret = GameJoy::JS_CSFrameSyncResponse::Instance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<GameJoy::JS_CSFrameSyncResponse>(cx, (GameJoy::JS_CSFrameSyncResponse*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_GameJoy_JS_CSFrameSyncResponse_Instance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_GameJoy_JS_CPP_Bridge_prototype;

void js_register_GameJoy_JS_CSFrameSyncResponse(JSContext *cx, JS::HandleObject global) {
    jsb_GameJoy_JS_CSFrameSyncResponse_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameJoy_JS_CSFrameSyncResponse_class->name = "JS_CSFrameSyncResponse";
    jsb_GameJoy_JS_CSFrameSyncResponse_class->addProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSFrameSyncResponse_class->delProperty = JS_DeletePropertyStub;
    jsb_GameJoy_JS_CSFrameSyncResponse_class->getProperty = JS_PropertyStub;
    jsb_GameJoy_JS_CSFrameSyncResponse_class->setProperty = JS_StrictPropertyStub;
    jsb_GameJoy_JS_CSFrameSyncResponse_class->enumerate = JS_EnumerateStub;
    jsb_GameJoy_JS_CSFrameSyncResponse_class->resolve = JS_ResolveStub;
    jsb_GameJoy_JS_CSFrameSyncResponse_class->convert = JS_ConvertStub;
    jsb_GameJoy_JS_CSFrameSyncResponse_class->finalize = jsb_ref_finalize;
    jsb_GameJoy_JS_CSFrameSyncResponse_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("get_steps", js_GameJoy_JS_CSFrameSyncResponse_get_steps, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_result", js_GameJoy_JS_CSFrameSyncResponse_get_result, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_steps", js_GameJoy_JS_CSFrameSyncResponse_set_steps, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_result", js_GameJoy_JS_CSFrameSyncResponse_set_result, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Instance", js_GameJoy_JS_CSFrameSyncResponse_Instance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_GameJoy_JS_CPP_Bridge_prototype);
    jsb_GameJoy_JS_CSFrameSyncResponse_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameJoy_JS_CSFrameSyncResponse_class,
        dummy_constructor<GameJoy::JS_CSFrameSyncResponse>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameJoy_JS_CSFrameSyncResponse_prototype);
    jsb_register_class<GameJoy::JS_CSFrameSyncResponse>(cx, jsb_GameJoy_JS_CSFrameSyncResponse_class, proto, parent_proto);
}

void register_all_GameJoy(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "GameJoy", &ns);

    js_register_GameJoy_JS_CPP_Bridge(cx, ns);
    js_register_GameJoy_JS_CSLoginResponse(cx, ns);
    js_register_GameJoy_JS_PBFrameMessage(cx, ns);
    js_register_GameJoy_JS_CSCreateRoomRequest(cx, ns);
    js_register_GameJoy_JS_CSFightReadyResponse(cx, ns);
    js_register_GameJoy_JS_CSFightReadyRequest(cx, ns);
    js_register_GameJoy_JS_CSFrameSyncRequest(cx, ns);
    js_register_GameJoy_JS_CSFrameSyncResponse(cx, ns);
    js_register_GameJoy_JS_CSRoomMessage(cx, ns);
    js_register_GameJoy_Proxy(cx, ns);
    js_register_GameJoy_JS_CSJoinRoomRequest(cx, ns);
    js_register_GameJoy_JS_CSCreateRoomResponse(cx, ns);
    js_register_GameJoy_JS_CSPullRoomsRequest(cx, ns);
    js_register_GameJoy_JS_CSJoinRoomResponse(cx, ns);
    js_register_GameJoy_JS_CSPullRoomsResponse(cx, ns);
    js_register_GameJoy_JS_CSLoginRequest(cx, ns);
}


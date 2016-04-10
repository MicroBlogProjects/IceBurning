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

JSClass  *jsb_GameJoy_JS_CSLoginResponse_class;
JSObject *jsb_GameJoy_JS_CSLoginResponse_prototype;

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
bool js_GameJoy_JS_CSLoginResponse_set_msgID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSLoginResponse* cobj = (GameJoy::JS_CSLoginResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSLoginResponse_set_msgID : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_GameJoy_JS_CSLoginResponse_set_msgID : Error processing arguments");
        cobj->set_msgID(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSLoginResponse_set_msgID : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_GameJoy_JS_CSLoginResponse_get_msgID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameJoy::JS_CSLoginResponse* cobj = (GameJoy::JS_CSLoginResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_GameJoy_JS_CSLoginResponse_get_msgID : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->get_msgID();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_GameJoy_JS_CSLoginResponse_get_msgID : wrong number of arguments: %d, was expecting %d", argc, 0);
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
        JS_FN("get_result", js_GameJoy_JS_CSLoginResponse_get_result, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_msgID", js_GameJoy_JS_CSLoginResponse_set_msgID, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_msgID", js_GameJoy_JS_CSLoginResponse_get_msgID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("get_uin", js_GameJoy_JS_CSLoginResponse_get_uin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_result", js_GameJoy_JS_CSLoginResponse_set_result, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("set_uin", js_GameJoy_JS_CSLoginResponse_set_uin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
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

void register_all_GameJoy(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "GameJoy", &ns);

    js_register_GameJoy_JS_CPP_Bridge(cx, ns);
    js_register_GameJoy_JS_CSLoginResponse(cx, ns);
    js_register_GameJoy_Proxy(cx, ns);
}


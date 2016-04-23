LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2djs_shared

LOCAL_MODULE_FILENAME := libcocos2djs

LOCAL_CPP_EXTENSION := .cc .cpp

LOCAL_SRC_FILES := hellojavascript/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/my/Common/Common_Tools.cpp \
                   ../../Classes/my/Common/Console_Output.cpp \
                   ../../Classes/my/Connect/ClientSocket.cpp \
                   ../../Classes/my/Connect/CMessage.cpp \
                   ../../Classes/my/JSvsCPP/BindPBWithJS.cpp \
                   ../../Classes/my/JSvsCPP/JS_CPP_Data_Exchange.cpp \
                   ../../Classes/my/JSvsCPP/jsb_GameJoy_auto.cpp \
                   ../../Classes/my/JSvsCPP/MessageProxy.cpp \
                   ../../Classes/my/ProtoOut/CreateRoom.pb.cc \
                   ../../Classes/my/ProtoOut/GamePlay.pb.cc \
                   ../../Classes/my/ProtoOut/Login.pb.cc \
                   ../../Classes/my/ProtoOut/MessageRegister.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../../../../../Common/protobuf-2.5.0/src \
                    $(LOCAL_PATH)/../../../../../../Common/Include

LOCAL_STATIC_LIBRARIES := cocos2d_js_static 

LOCAL_WHOLE_STATIC_LIBRARIES += tot_protobuf_static
#LOCAL_WHOLE_STATIC_LIBRARIES += protobuf_static
#LOCAL_WHOLE_STATIC_LIBRARIES += protobuf_lite_static
#LOCAL_WHOLE_STATIC_LIBRARIES += protoc_static

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=2 -DCOCOS2D_JAVASCRIPT

include $(BUILD_SHARED_LIBRARY)


$(call import-module, scripting/js-bindings/proj.android)
$(call import-module, ../../../../../Common/protobuf-2.5.0)
#$(call import-module, ../../../../../Common/protobuf-2.5.0/android_libprotobuf)
#$(call import-module, ../../../../../Common/protobuf-2.5.0/android_libprotobuf_lite)
#$(call import-module, ../../../../../Common/protobuf-2.5.0/android_libprotoc)
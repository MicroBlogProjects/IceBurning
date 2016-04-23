LOCAL_PATH := $(call my-dir)  
  
include $(CLEAR_VARS)  
LOCAL_MODULE := protobuf_lite_static  
LOCAL_MODULE_FILENAME := libprotobuf_lite
LOCAL_SRC_FILES := ./libprotobuf-lite.a 
include $(BUILD_STATIC_LIBRARY)  
LOCAL_PATH := $(call my-dir)  
  
include $(CLEAR_VARS)
LOCAL_MODULE := protoc_static
LOCAL_MODULE_FILENAME := libprotoc
LOCAL_SRC_FILES := ./libprotoc.a  
include $(BUILD_STATIC_LIBRARY)
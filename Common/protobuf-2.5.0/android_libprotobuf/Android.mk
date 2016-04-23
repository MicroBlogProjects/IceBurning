LOCAL_PATH := $(call my-dir)  
  
include $(CLEAR_VARS)  
LOCAL_MODULE := protobuf_static  
LOCAL_MODULE_FILENAME := libprotobuf
LOCAL_SRC_FILES := ./libprotobuf.a        
include $(BUILD_STATIC_LIBRARY)  
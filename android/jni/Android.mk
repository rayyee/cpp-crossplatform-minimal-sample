LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

CPP_PATH := ../../cpp

LOCAL_MODULE := ComboSample
LOCAL_SRC_FILES := MainActivity.cpp GLRenderer.cpp
LOCAL_SRC_FILES += AndroidMain.cpp $(CPP_PATH)/StateManager.cpp $(CPP_PATH)/GLDrawer.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)../../cpp $(NDK_MODULE_PATH)/gpg-cpp-sdk/android/include

LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv1_CM -lGLESv2 -lz
LOCAL_STATIC_LIBRARIES := gpg-1 gnustl-static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,gpg-cpp-sdk/android)

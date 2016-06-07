LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := gmp-prebuilt
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libgmp.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include/$(TARGET_ARCH_ABI)
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := gmpjni
LOCAL_SRC_FILES := org_gmplib_gmpjni_GMP.cpp org_gmplib_gmpjni_GMP_mpz_t.cpp org_gmplib_gmpjni_GMP_mpq_t.cpp org_gmplib_gmpjni_GMP_mpf_t.cpp org_gmplib_gmpjni_GMP_randstate_t.cpp
LOCAL_SHARED_LIBRARIES := gmp-prebuilt
include $(BUILD_SHARED_LIBRARY)

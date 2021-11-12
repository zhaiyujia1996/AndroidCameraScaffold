//
// Created by ZHP on 2021/7/13.
//

#ifndef ZHP_CXX_ENTRANCE_JAVA_SUPPORT_H
#define ZHP_CXX_ENTRANCE_JAVA_SUPPORT_H

#include <jni.h>
#include <sstream>
#include <iomanip>
#include <sys/prctl.h>

#include "JniHelper/ScopedUtfChars.h"
#include "JniHelper/ScopedLocalRef.h"

#include "CxxResult.h"



/* ======================================================= */
/* Public Methods                                          */
/* ======================================================= */

JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *reserved);


/* ======================================================= */
/* Java Native Methods Implementation                      */
/* ======================================================= */

extern "C" JNIEXPORT
jstring JNICALL Java_me_haipeng_scaffold_camera_cxx_CxxEntrance_javaCallCxx(
        JNIEnv *env,
        jclass self,
        jstring action,
        jstring params
);



/* ======================================================= */
/* Public Methods                                          */
/* ======================================================= */

/**
 * C++ 调用 Java 层的方法。
 * 注意： 返回值不用时，需要调用 freeData。
 */
CxxResult cxxCallJava(const std::string &actionType, const std::string &json);

/**
 * C++ 调用 Java 层的方法。
 * 注意： 返回值不用时，需要调用 freeData。
 */
CxxResult cxxCallJava(const std::string &actionType);



/* ======================================================= */
/* Private Methods                                         */
/* ======================================================= */

void registerDefaultCxxFunctions();


#endif

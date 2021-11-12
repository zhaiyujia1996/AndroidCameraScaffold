//
// Created by ZHP on 2021/7/12.
//

#ifndef ZHP_CXX_ENTRANCE_LOG_H
#define ZHP_CXX_ENTRANCE_LOG_H

#include <string>
#include <jni.h>
#include <android/log.h>


/**
 * 日志相关
 */
class CxxEntranceLog {

    /* ======================================================= */
    /* Public Methods                                          */
    /* ======================================================= */
public:

    static void v(const std::string& msg) {
        __android_log_print(ANDROID_LOG_VERBOSE, "CxxEntrance", "%s", msg.c_str());
    }

    static void d(const std::string& msg) {
        __android_log_print(ANDROID_LOG_DEBUG, "CxxEntrance", "%s", msg.c_str());
    }

    static void i(const std::string& msg) {
        __android_log_print(ANDROID_LOG_INFO, "CxxEntrance", "%s", msg.c_str());
    }

    static void w(const std::string& msg) {
        __android_log_print(ANDROID_LOG_WARN, "CxxEntrance", "%s", msg.c_str());
    }

    static void e(const std::string& msg) {
        __android_log_print(ANDROID_LOG_ERROR, "CxxEntrance", "%s", msg.c_str());
    }

};

#endif

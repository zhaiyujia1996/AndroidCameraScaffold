//
// Created by ZHP on 2021/7/13.
//

#include <jni.h>
#include <sstream>
#include <iomanip>
#include <sys/prctl.h>

#include "JniHelper/ScopedUtfChars.h"
#include "JniHelper/ScopedLocalRef.h"

#include "CxxResult.h"
#include "CxxEntranceCodes.h"
#include "CxxEntranceJavaSupport.h"
#include "CxxFunctionsHolder.h"
#include "CxxEntranceUtils.h"

#include "./camera/CameraAnalyzer.h"

/* ======================================================= */
/* Fields                                                  */
/* ======================================================= */

/** 全局的 JavaVM 对象 */
JavaVM *javaVM = nullptr;

/** Java 层的 SmartEye 类对象 */
jclass JavaCxxEntranceClassRef = nullptr;

/** Java 层的函数 */
jmethodID methodCxxCallJava = nullptr;



/* ======================================================= */
/* Public Methods                                          */
/* ======================================================= */

JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    // 保存虚拟机的引用
    javaVM = vm;

    // 获取环境
    JNIEnv *env;
    jint r = vm->GetEnv((void **) &env, JNI_VERSION_1_4);
    if (r != JNI_OK) {
        return r;
    }

    ScopedLocalRef<jclass> uClass(env, env->FindClass("me/haipeng/scaffold/camera/cxx/CxxEntrance"));

    // 获取 Java 层的类
    JavaCxxEntranceClassRef = (jclass) (env->NewGlobalRef(uClass.get()));

    // 保存 Java 的方法到 C++ 中
    const char* methodName = "cxxCallJava";
    const char* methodSignature = "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;";
    methodCxxCallJava = env->GetStaticMethodID(JavaCxxEntranceClassRef, methodName, methodSignature);

    // 注册一个默认的方法
    registerDefaultCxxFunctions();

    return JNI_VERSION_1_4;
}



/* ======================================================= */
/* Java Native Methods Implementation                      */
/* ======================================================= */

extern "C" JNIEXPORT
jstring JNICALL Java_me_haipeng_scaffold_camera_cxx_CxxEntrance_javaCallCxx(
        JNIEnv *env,
        jclass self,
        jstring action,
        jstring params)
{
    ScopedUtfChars _action(env, action);
    std::string actionString = std::string(_action.c_str());

    auto function = CxxFunctionsHolder::get(actionString);
    if (!function) {
        return env->NewStringUTF("0002");
    }

    ScopedUtfChars _params(env, params);
    std::string paramsString = std::string(_params.c_str());
    auto res = function(paramsString);
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << res.code << res.data;
    return env->NewStringUTF(oss.str().c_str());
}



/* ======================================================= */
/* Public Methods                                          */
/* ======================================================= */

/**
 * C++ 调用 Java 层的方法。
 * 注意： 返回值不用时，需要调用 freeData。
 */
CxxResult cxxCallJava(const std::string &actionType, const std::string &json) {
    JNIEnv *env = nullptr;
    bool needDetach = false;

    // 判断当前 C++ 的线程是否已经绑定到 JVM 的环境中了，如果没有，需要绑定
    if (javaVM->GetEnv((void **) &env, JNI_VERSION_1_4) == JNI_EDETACHED) {

        // 线程名会丢失，所以需要先保存线程名
        char threadName[32] = {0};
        prctl(PR_GET_NAME, threadName);

        // 设置绑定参数
        JavaVMAttachArgs args;
        args.version = JNI_VERSION_1_4;
        args.name = (char *) threadName;
        args.group = nullptr;

        // 绑定线程
        int attachResult = javaVM->AttachCurrentThread(&env, &args);
        if (attachResult != JNI_OK) {
            CxxResult res{};
            res.code = CxxEntranceCodes::CODE_ERROR;
            res.data = CxxEntranceUtils::mallocEmptyChars();
            return res;
        }

        needDetach = true;
    }

    if (JavaCxxEntranceClassRef == nullptr) {
        CxxResult res{};
        res.code = CxxEntranceCodes::CODE_ERROR;
        res.data = CxxEntranceUtils::mallocEmptyChars();
        return res;
    }

    if (methodCxxCallJava == nullptr) {
        CxxResult res{};
        res.code = CxxEntranceCodes::CODE_ERROR;
        res.data = CxxEntranceUtils::mallocEmptyChars();
        return res;
    }

    // 参数类型转换
    const char *_actionType = actionType.c_str();
    jstring actionUtf = env->NewStringUTF(_actionType);

    const char *_json = json.c_str();
    jstring jsonUtf = env->NewStringUTF(_json);

    // 调用 Java 层的方法，获取返回值
    auto response = (jstring) env->CallStaticObjectMethod(JavaCxxEntranceClassRef, methodCxxCallJava, actionUtf, jsonUtf);

    // 释放不再使用的对象
    //    env->DeleteLocalRef(actionUtf);
    //    env->DeleteLocalRef(jsonUtf);
    //
    //    // Detach 如果需要
    //    if (needDetach) {
    //        javaVM->DetachCurrentThread();
    //    }
    // TODO：上面这几行不注释掉，下面会崩溃，稍后排查

    // 将返回值做类型转换
    ScopedUtfChars _response(env, response);
    std::string cxxResponse = std::string(_response.c_str());

    if (cxxResponse.length() >= 4) {
        CxxResult res{};
        res.code = strtol(cxxResponse.substr(0, 4).c_str(), nullptr, 10);
        res.data = CxxEntranceUtils::createNewCharsFromString(cxxResponse.substr(4, cxxResponse.length() - 4));
        return res;
    } else {
        CxxResult res{};
        res.code = CxxEntranceCodes::CODE_ERROR;
        res.data = CxxEntranceUtils::mallocEmptyChars();
        return res;
    }
}

/**
 * C++ 调用 Java 层的方法。
 * 注意： 返回值不用时，需要调用 freeData。
 */
CxxResult cxxCallJava(const std::string &actionType) {
    std::string empty;
    return cxxCallJava(actionType, empty);
}



/* ======================================================= */
/* Private Methods                                         */
/* ======================================================= */

void registerDefaultCxxFunctions() {

    // 注册 「验证 C++ 是否可以调通」 的方法
    CxxFunctionsHolder::registerFunction("Hello C++, I'm Java", []() {
        // 返回结果给 Java 层
        auto data = std::string("HP so handsome!");
        auto cxxResponse = HandlerResult::success();
        cxxResponse.data = data;
        return cxxResponse;
    });


    // 注册 「相机关闭」 的方法。
    CxxFunctionsHolder::registerFunction("OnCameraClosed", [](const std::string& params) {
        std::string res = CameraAnalyzer::onCameraClosed(params);
        HandlerResult result;
        auto cxxResponse = HandlerResult::success();
        cxxResponse.data = res;
        return cxxResponse;
    });
}

extern "C"
JNIEXPORT void JNICALL
Java_me_haipeng_scaffold_camera_cxx_CxxEntrance_onCameraPreviewUpdate(JNIEnv *env, jclass clazz, jintArray pixels) {
    int length = env->GetArrayLength(pixels);

    jboolean isCopy;
    int* argb = env->GetIntArrayElements(pixels, &isCopy);
    CameraAnalyzer::onCameraPreviewUpdate(argb, length);
}
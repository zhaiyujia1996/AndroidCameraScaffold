//
// Created by ZHP on 2021/7/12.
//

#ifndef ZHP_CXX_FUNCTIONS_HOLDER_H
#define ZHP_CXX_FUNCTIONS_HOLDER_H

#include <functional>
#include <string>
#include <map>

/**
 * 定义： C++ 函数的返回值。
 */
class HandlerResult {
public:

    /* ======================================================= */
    /* Fields                                                  */
    /* ======================================================= */

    int32_t code;
    std::string data;



    /* ======================================================= */
    /* Public Methods                                          */
    /* ======================================================= */

    /**
     * 创建一个新的 HandlerResult 对象， code 值为 CODE_SUCCESS。
     */
    static HandlerResult success();

    /**
     * 创建一个新的 HandlerResult 对象.
     */
    static HandlerResult withCode(int32_t code);
};



/**
 * 定义： C++ 的函数。
 */
using CxxFunction = std::function<HandlerResult(std::string)>;



/**
 * 用于保存 C++ 支持的方法的包装类。
 */
class CxxFunctionsHolder {

    /* ======================================================= */
    /* Fields                                                  */
    /* ======================================================= */

public:

    /**
     * 保存已经注册的方法。
     */
    static std::map<std::string, CxxFunction> functions;



    /* ======================================================= */
    /* Public Methods                                          */
    /* ======================================================= */

public:

    /**
     * 注册一个可供调用的方法。
     */
    static void registerFunction(const std::string& action, const CxxFunction& function) {
        functions[action] = function;
    }

    /**
     * 注册一个可供调用的方法。
     */
    static void registerFunction(const std::string& action, const std::function<HandlerResult()>& function) {
        functions[action] = [function](const std::string& nil) {
            return function();
        };
    }

    /**
     * 获取对应 action 的实现。
     */
    static CxxFunction get(const std::string& action) {
        return functions[action];
    }


};

#endif

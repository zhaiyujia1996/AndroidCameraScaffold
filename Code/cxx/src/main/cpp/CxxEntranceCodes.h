//
// Created by ZHP on 2021/7/13.
//

#ifndef ZHP_CXX_ENTRANCE_CODES_H
#define ZHP_CXX_ENTRANCE_CODES_H

class CxxEntranceCodes {

public:

    /* ======================================================= */
    /* Fields                                                  */
    /* ======================================================= */

    /**
     * 未知，用于赋初始值
     */
    static const int CODE_UNKNOWN          = 0;

    /**
     * 通道异常，可能是 CxxEntrance 没有初始化
     */
    static const int CODE_CHANNEL_ERROR    = 1;

    /**
     * C++ 中没有找到对应 action 的方法
     */
    static const int CODE_NO_SUCH_FUNCTION = 2;

    /**
     * C++ 方法调用成功
     */
    static const int CODE_SUCCESS          = 3;

    /**
     * 其他异常
     */
    static const int CODE_ERROR            = 4;

};

#endif

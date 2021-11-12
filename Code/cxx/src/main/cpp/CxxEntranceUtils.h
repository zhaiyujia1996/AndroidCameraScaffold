//
// Created by ZHP on 2021/7/13.
//

#ifndef ZHP_CXX_ENTRANCE_UTILS_H
#define ZHP_CXX_ENTRANCE_UTILS_H

#include <string>

/**
 * 一些工具类。
 *
 * @author 郑海鹏
 * @since  2021年07月13日11:53:15
 */
class CxxEntranceUtils {
public:

    /* ======================================================= */
    /* Public Methods                                          */
    /* ======================================================= */

    /**
     * 申请一个空字符串的 char 指针。
     */
    static char* mallocEmptyChars();

    /**
     * 从 data 创建一个新的 char 指针。
     * 用于传递到 Dart 端等。
     */
    static char* createNewCharsFromString(const std::string& data);

};


#endif

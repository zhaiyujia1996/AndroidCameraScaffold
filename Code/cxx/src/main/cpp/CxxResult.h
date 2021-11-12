//
// Created by ZHP on 2021/7/13.
//

#ifndef ZHP_CXX_ENTRANCE_CXX_RESULT_H
#define ZHP_CXX_ENTRANCE_CXX_RESULT_H

#include <utility>

struct CxxResult {
    int32_t code;
    char* data = nullptr;

    void freeData() {
        if (data != nullptr) {
            free(data);
            data = nullptr;
        }
    }
};

#endif

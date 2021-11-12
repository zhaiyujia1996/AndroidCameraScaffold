//
// Created by ZHP on 2021/7/12.
//




#include <map>
#include "CxxFunctionsHolder.h"
#include "CxxEntranceCodes.h"

std::map<std::string, CxxFunction> CxxFunctionsHolder::functions;


HandlerResult HandlerResult::success() {
    HandlerResult res;
    res.code = CxxEntranceCodes::CODE_SUCCESS;
    return res;
}

HandlerResult HandlerResult::withCode(int32_t code) {
    HandlerResult res;
    res.code = code;
    return res;
}
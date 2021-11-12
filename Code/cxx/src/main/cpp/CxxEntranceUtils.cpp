//
// Created by ZHP on 2021/7/13.
//

#include "CxxEntranceUtils.h"
#include <utility>

char* CxxEntranceUtils::mallocEmptyChars() {
    char* response = (char*) malloc(sizeof(char));
    response[0] = '\0';
    return response;
}

char* CxxEntranceUtils::createNewCharsFromString(const std::string& data) {
    auto chars = data.c_str();
    int length = data.length();
    char* response = (char*) malloc((length + 1) * sizeof(char));
    memcpy(response, chars, length);
    response[length] = '\0';
    return response;
}
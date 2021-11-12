//
// Created by ZHP on 2021/11/12.
//

#include "CameraAnalyzer.h"
#include "../CxxEntranceLog.h"

std::string CameraAnalyzer::onCameraClosed(const std::string& params) {
    CxxEntranceLog::i("C++层收到 onCameraClosed 消息");
    return "";
}

void CameraAnalyzer::onCameraPreviewUpdate(int *argb, int length) {
    CxxEntranceLog::i("C++层收到 onCameraPreviewUpdate 消息");
}

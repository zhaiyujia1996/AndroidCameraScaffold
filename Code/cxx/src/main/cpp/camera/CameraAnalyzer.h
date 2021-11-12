//
// Created by ZHP on 2021/11/12.
//

#ifndef ZHP_CXX_CAMERA_ANALYZER_H
#define ZHP_CXX_CAMERA_ANALYZER_H

#include <string>

/**
 * 处理相机相关逻辑。
 */
class CameraAnalyzer {


public:

    /**
     * Java 层关闭相机时，调用这个方法。
     */
    static std::string onCameraClosed(const std::string& params);

    /**
     * 预览画面更新的通知。
     * @param argb 画面像素数据
     * @param length argb 数组的长度。
     */
    static void onCameraPreviewUpdate(int* argb, int length);
};


#endif //ZHP_CXX_CAMERA_ANALYZER_H

# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

add_library(
        CxxEntrance
        SHARED
        CxxEntranceJavaSupport.h
        CxxEntranceJavaSupport.cpp
        CxxEntranceLog.h
        CxxEntrance.cpp
        CxxFunctionsHolder.h
        CxxFunctionsHolder.cpp
        CxxEntranceUtils.h
        CxxEntranceUtils.cpp
        CxxResult.h
        camera/CameraAnalyzer.cpp
        camera/CameraAnalyzer.h
)
find_library( log-lib log )

# 获取基础库目录
target_link_libraries( CxxEntrance ${log-lib})
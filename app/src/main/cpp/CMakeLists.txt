
cmake_minimum_required(VERSION 3.22.1)

project("main")


set(CMAKE_C_COMPILER ${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/bin/clang)
set(CMAKE_CXX_COMPILER ${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++)

include_directories(src ../../../../libs/SDL/include)
add_subdirectory(../../../../ ${CMAKE_BINARY_DIR}/libs/core )


add_library(${CMAKE_PROJECT_NAME} SHARED native-lib.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}
        core
        ${GLESv2_LIB}
        EGL
        GLESv2
        android
        log
        )
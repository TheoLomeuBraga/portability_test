#include <jni.h>
#include <string>
#include "../../../../src/main.h"
#include <thread>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    //start();
    std::thread start_thread(start);
    start_thread.detach();
    
    return env->NewStringUTF(hello.c_str());
}
#include "sence.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_opengldemo_NativeInterface_initOpenGL(JNIEnv *env, jclass type) {
    initGL();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_opengldemo_NativeInterface_changeViewPort(JNIEnv *env, jclass type, jfloat width,
        jfloat height) {
    changeViewPort(width,height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_opengldemo_NativeInterface_onDraw(JNIEnv *env, jclass type){
    drawOneFrame();
}
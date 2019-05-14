#pragma once

#include "ggl.h"

void initGL();
void changeViewPort(float width, float height);
void drawOneFrame();

void initAssetManager(JNIEnv *env, jobject assetManager);

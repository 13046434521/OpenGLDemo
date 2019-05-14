package com.jtl.opengldemo;

import android.content.res.AssetManager;

/**
 * 作者:jtl
 * 日期:Created in 2019/5/13 11:58
 * 描述:
 * 更改:
 */
public class NativeInterface {
    static {
        System.loadLibrary("native-lib");
    }

    public static native void initAssetManager(AssetManager assetManager);

    public static native void initOpenGL();

    public static native void changeViewPort(float width,float height);

    public static native void onDraw();
}

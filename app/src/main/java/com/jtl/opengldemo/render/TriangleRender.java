package com.jtl.opengldemo.render;

import android.content.Context;
import android.opengl.GLSurfaceView;

import com.jtl.opengldemo.NativeInterface;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * 作者:jtl
 * 日期:Created in 2019/5/13 11:57
 * 描述:
 * 更改:
 */
public class TriangleRender implements GLSurfaceView.Renderer {
    private Context mContext;

    public TriangleRender(Context context) {
        mContext = context;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        NativeInterface.initAssetManager(mContext.getAssets());
        NativeInterface.initOpenGL();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        NativeInterface.changeViewPort(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        NativeInterface.onDraw();
    }
}

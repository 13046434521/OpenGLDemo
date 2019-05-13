package com.jtl.opengldemo;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import com.jtl.opengldemo.render.TriangleRender;

import javax.microedition.khronos.opengles.GL;

/**
 * 作者:jtl
 * 日期:Created in 2019/5/13 13:36
 * 描述:
 * 更改:
 */
public class DemoGLSurface extends GLSurfaceView {
    private TriangleRender mTriangleRender;
    public DemoGLSurface(Context context) {
        this(context,null);
    }

    public DemoGLSurface(Context context, AttributeSet attrs) {
        super(context, attrs);

        init();
    }

    private void init(){
        mTriangleRender=new TriangleRender();

        this.setEGLContextClientVersion(2);
        this.setRenderer(mTriangleRender);
        this.setRenderMode(RENDERMODE_CONTINUOUSLY);
    }
}

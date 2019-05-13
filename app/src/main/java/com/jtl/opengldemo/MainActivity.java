package com.jtl.opengldemo;

import android.opengl.GLSurfaceView;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.jtl.opengldemo.render.TriangleRender;

public class MainActivity extends AppCompatActivity {
    private DemoGLSurface mGLSurfaceView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mGLSurfaceView=findViewById(R.id.gl_main_surface);
    }
}

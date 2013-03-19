package com.example.helloopengljni;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.app.Activity;

public class HelloOpenGLJNIActivity extends Activity {

	private GLSurfaceView mGLview;
	private GLSurfaceView.Renderer mRenderer;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        mGLview = new CustomGLView(this);
        mRenderer = new CustomRenderer();
        setContentView(mGLview);
        mGLview.setRenderer(mRenderer);
        
        //Entweder hier SeekBars hinzufügen oder im Layout
    }
}

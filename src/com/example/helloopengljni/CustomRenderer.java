package com.example.helloopengljni;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.graphics.Matrix;
import android.opengl.GLSurfaceView;

public class CustomRenderer implements GLSurfaceView.Renderer {
	static{
		System.loadLibrary("renderer");
	}
	
	public static native void init(int width, int height);
    public static native void step();
	
	@Override
	public void onDrawFrame(GL10 gl) {
		step();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		init(width, height);
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
	}

}

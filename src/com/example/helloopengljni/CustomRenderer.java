package com.example.helloopengljni;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;

public class CustomRenderer implements GLSurfaceView.Renderer {
	
	@Override
	public void onDrawFrame(GL10 gl) {
		//Zeichnen Funktion
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		//Funktion, die den Viewport neu setzt
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
	}

}

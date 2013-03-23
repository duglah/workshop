package com.example.helloopengljni;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.ViewGroup.LayoutParams;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.app.Activity;

public class HelloOpenGLJNIActivity extends Activity {

	private GLSurfaceView mGLview;
	private GLSurfaceView.Renderer mRenderer;
	
	static{
		System.loadLibrary("renderer");
	}
	
	public static native void setColor(float r, float g, float b);
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        mGLview = new CustomGLView(this);
        mRenderer = new CustomRenderer();
        setContentView(mGLview);
        mGLview.setRenderer(mRenderer);
        
        LinearLayout ll = new LinearLayout(this);
        ll.setOrientation(LinearLayout.VERTICAL);
        
        final SeekBar bar_red = new SeekBar(this);
        final SeekBar bar_green = new SeekBar(this);
        final SeekBar bar_blue = new SeekBar(this);
        
        bar_red.setMax(255);
        bar_green.setMax(255);
        bar_blue.setMax(255);
        
        bar_red.setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.WRAP_CONTENT));
        bar_green.setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.WRAP_CONTENT));
        bar_blue.setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.WRAP_CONTENT));
        
        ll.addView(bar_red);
        ll.addView(bar_green);
        ll.addView(bar_blue);
        
        addContentView(ll, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
        
        bar_red.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
			
			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				// TODO Auto-generated method stub
				setColor(bar_red.getProgress()/255.0f,bar_green.getProgress()/255.0f,bar_blue.getProgress()/255.0f);
			}
		
		});
        
        bar_green.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
			
			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				// TODO Auto-generated method stub
				setColor(bar_red.getProgress()/255.0f,bar_green.getProgress()/255.0f,bar_blue.getProgress()/255.0f);
			}
		});
        
        bar_blue.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
			
			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				// TODO Auto-generated method stub
				setColor(bar_red.getProgress()/255.0f,bar_green.getProgress()/255.0f,bar_blue.getProgress()/255.0f);
				
			}
		});
    }
}

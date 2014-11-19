/* Copyright (c) 2014 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.google.example.combosample;

import android.app.Activity;
import android.content.Intent;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;

/**
 * Main Activity for this sample. Implements Android buttons to control sign-in
 * and sign-out as well as showing leaderboards and achievements. The buttons
 * trigger functions in the Google Play Games C++ SDK which are in shared C++
 * code. Also displays a GLSurfaceView which is controlled by a renderer
 * implemented in shared C++ code.
 *
 * @author Sam Stern (samstern@google.com)
 */
public class MainActivity extends Activity implements OnClickListener {

    private static final String TAG = MainActivity.class.getSimpleName();

    private GLSurfaceView mGlView;
    private boolean mIsSignedIn = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Set a callback function for the C++ code to invoke after an
        // authorization event ends.
        // This should be the String name of a public, void, non-static method
        // in this class that
        // takes a single boolean as an argument.
        setAuthResultCallback("onAuthActionFinished");

        // Initialize the Google Play Games C++ SDK. This will set up the proper
        // Android platform
        // configuration and make an initial attempt to sign in without user
        // interaction.
        nativeOnActivityCreated(this, savedInstanceState);

        // Button click handlers
        findViewById(R.id.sign_in_button).setOnClickListener(this);
        findViewById(R.id.sign_out_button).setOnClickListener(this);
        findViewById(R.id.show_achievements_button).setOnClickListener(this);
        findViewById(R.id.show_leaderboards_button).setOnClickListener(this);

        // Enable/disable buttons based on sign-in state
        setButtonState();

        // Configure OpenGL view and renderer
        mGlView = (GLSurfaceView) findViewById(R.id.gl_surface_view);
        mGlView.setEGLContextClientVersion(2);
        mGlView.setRenderer(new GLRenderer());
    }

    @Override
    protected void onPause() {
        super.onPause();
        mGlView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mGlView.onResume();
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent result) {
        super.onActivityResult(requestCode, resultCode, result);
        Log.i(TAG, "OnActivityResult: " + requestCode);

        // Pass the activity result to the C++ SDK so that it can resolve any
        // errors related
        // to Google Play Games. The C++ SDK only acts on Activity results that
        // contain the
        // unique request code.
        nativeOnActivityResult(this, requestCode, resultCode, result);
    }

    public void onAuthActionFinished(boolean success) {
        Log.i(TAG, "onAuthActionFinished: " + String.valueOf(success));
        mIsSignedIn = success;

        // Need to make sure to run this on the UI thread since the C++ SDK may
        // invoke this
        // callback from a separate thread.
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                setButtonState();
            }
        });
    }

    /**
     * Enable/disable buttons based on Google Play Games sign-in state.
     */
    private void setButtonState() {
        findViewById(R.id.sign_in_button).setEnabled(!mIsSignedIn);
        findViewById(R.id.sign_out_button).setEnabled(mIsSignedIn);
        findViewById(R.id.show_achievements_button).setEnabled(mIsSignedIn);
        findViewById(R.id.show_leaderboards_button).setEnabled(mIsSignedIn);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.sign_in_button:
                signIn();
                break;
            case R.id.sign_out_button:
                signOut();
                break;
            case R.id.show_achievements_button:
                showAchievements();
                break;
            case R.id.show_leaderboards_button:
                showLeaderboards();
                break;
            default:
                Log.w(TAG, "Click on unidentified view id: " + v.getId());
                break;
        }
    }

    private native void signIn();

    private native void signOut();

    private native void showAchievements();

    private native void showLeaderboards();

    private native void nativeOnActivityCreated(Activity activity,
            Bundle savedInstanceState);

    private native void nativeOnActivityResult(Activity activity,
            int request_code, int result_code, Intent result);

    private native void setAuthResultCallback(String methodName);

    static {
        System.loadLibrary("ComboSample");
    }
}

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

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView.Renderer;

/**
 * Wrapper class that calls the native functions in jni/GLRenderer.cpp.
 * GLRenderer uses the shared C++ class in cpp/GlDrawer.cpp to control what is
 * drawn on the GL view.
 *
 * @author Sam Stern (samstern@google.com)
 */
public class GLRenderer implements Renderer {

    public GLRenderer() {
        initialize();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        nativeOnSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        nativeOnSurfaceChanged();
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        nativeOnUpdate();
        nativeOnDrawFrame();
    }

    private native void initialize();

    private native void nativeOnSurfaceCreated();

    private native void nativeOnSurfaceChanged();

    private native void nativeOnDrawFrame();

    private native void nativeOnUpdate();

    static {
        System.loadLibrary("ComboSample");
    }
}

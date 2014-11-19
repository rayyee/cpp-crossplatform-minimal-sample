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

#include "GLRenderer.h"

#include "../../cpp/GLDrawer.h"

/**
 * An instance of GLDrawer to use to draw on the GLSurfaceView.
 */
namespace {
    GLDrawer *gld;
}

JNIEXPORT void JNICALL Java_com_google_example_combosample_GLRenderer_initialize
  (JNIEnv *, jobject) {

    gld = new GLDrawer();
}

JNIEXPORT void JNICALL Java_com_google_example_combosample_GLRenderer_nativeOnSurfaceCreated
  (JNIEnv *, jobject) {

  	gld->onSurfaceCreated();
}

JNIEXPORT void JNICALL Java_com_google_example_combosample_GLRenderer_nativeOnSurfaceChanged
  (JNIEnv *, jobject) {

  	gld->onSurfaceChanged();
}

JNIEXPORT void JNICALL Java_com_google_example_combosample_GLRenderer_nativeOnDrawFrame
  (JNIEnv *, jobject) {

  	gld->onDrawFrame();
}

JNIEXPORT void JNICALL Java_com_google_example_combosample_GLRenderer_nativeOnUpdate
  (JNIEnv *, jobject) {

  	gld->onUpdate();
}

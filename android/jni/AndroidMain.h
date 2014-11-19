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

#ifndef ANDROID_MAIN_H
#define ANDROID_MAIN_H

#include <jni.h>

#include <android/log.h>

#include "gpg/android_initialization.h"
#include "gpg/android_support.h"

#include "../../cpp/StateManager.h"
#include "../../cpp/logging.h"

class AndroidMain {
    public:
        static void OnLoad(JavaVM *vm);
        static void NativeOnActivityCreated(JNIEnv *env, jobject activity, jobject savedInstanceState);
        static void SetAuthResultCallback(JNIEnv * env, jobject thiz, jstring callback);
    private:
        static JavaVM *jvm;
        static char *callbackName_;
        static jobject callbackObj_;
        static jmethodID callbackMID_;
};

#endif

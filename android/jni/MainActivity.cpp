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

#include <string.h>
#include <jni.h>

#include "MainActivity.h"
#include "AndroidMain.h"

#include "gpg/debug.h"

#include "../../cpp/logging.h"
#include "../../cpp/StateManager.h"

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;

    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
       return -1;
    }

    AndroidMain::OnLoad(vm);

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL Java_com_google_example_combosample_MainActivity_nativeOnActivityCreated
    (JNIEnv* env, jobject thiz, jobject activity, jobject savedInstanceState) {

    AndroidMain::NativeOnActivityCreated(env, activity, savedInstanceState);
}

JNIEXPORT void JNICALL Java_com_google_example_combosample_MainActivity_nativeOnActivityResult
    (JNIEnv* env, jobject thiz, jobject activity, jint request_code, jint result_code, jobject result) {

    // Forward activity result to GPG
    gpg::AndroidSupport::OnActivityResult(env, activity, request_code, result_code, result);

}

JNIEXPORT void JNICALL Java_com_google_example_combosample_MainActivity_signIn
    (JNIEnv* env, jobject thiz) {

    StateManager::BeginUserInitiatedSignIn();
}

JNIEXPORT void JNICALL Java_com_google_example_combosample_MainActivity_signOut
    (JNIEnv* env, jobject thiz) {

    StateManager::SignOut();
}

JNIEXPORT void JNICALL Java_com_google_example_combosample_MainActivity_showAchievements
  (JNIEnv *, jobject) {

    StateManager::ShowAchievements();
 }

JNIEXPORT void JNICALL Java_com_google_example_combosample_MainActivity_showLeaderboards
  (JNIEnv *, jobject) {

    StateManager::GetGameServices()->Leaderboards().ShowAllUI();
}

JNIEXPORT void JNICALL Java_com_google_example_combosample_MainActivity_setAuthResultCallback
  (JNIEnv * env, jobject thiz, jstring callback) {

    AndroidMain::SetAuthResultCallback(env, thiz, callback);
}

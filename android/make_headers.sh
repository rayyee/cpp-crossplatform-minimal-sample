#!/bin/bash
# Copyright (c) 2014 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ANDROID_TARGET='android-10'
DEST_DIR='./jni'
LOCAL_CLASSPATH='./bin/classes'
PACKAGE_NAME='com.google.example.combosample'

CLASSES=( "MainActivity" "GLRenderer" )
DESTINATIONS=( "MainActivity.h" "GLRenderer.h" )

echo "Creating native headers..."

for ((i=0; i<${#CLASSES[@]}; ++i)); do
	printf "%s --> %s\n" "${CLASSES[i]}" "$DEST_DIR/${DESTINATIONS[i]}"

	javah \
  		-classpath $LOCAL_CLASSPATH:$SDK_ROOT/platforms/$ANDROID_TARGET/android.jar \
  		-o $DEST_DIR/${DESTINATIONS[i]} \
  		-jni $PACKAGE_NAME.${CLASSES[i]}
done

echo "Done."


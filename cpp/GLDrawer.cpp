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

#include "GLDrawer.h"

GLDrawer::GLDrawer() {
	increasing_ = true;
	red_ = 0.0f;
}

void GLDrawer::onSurfaceCreated() {
	glClearColor(red_, 0.5f, 0.5f, 1.0f);
}

void GLDrawer::onSurfaceChanged() {
	// No-op
}

void GLDrawer::onDrawFrame() {
	glClearColor(red_, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLDrawer::onUpdate() {
	// Increment red if increasing, decrement otherwise
	float diff = increasing_ ? 0.01f : -0.01f;

	// Increment red up to 1.0, then back down to 0.0, repeat.
	red_ += diff;
	if (red_ >= 1.0f) {
		increasing_ = false;
	} else if (red_ <= 0.0f) {
		increasing_ = true;
	}
}

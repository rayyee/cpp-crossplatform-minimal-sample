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
 
#ifndef LOGGING_H
#define LOGGING_H

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>

const int32_t BUFFER_SIZE = 256;

// Wrap macro in do/while to ensure ;
#define LOGI(...) do { \
    char c[BUFFER_SIZE]; \
    snprintf(c, BUFFER_SIZE, __VA_ARGS__); \
    CFStringRef str = CFStringCreateWithCString(kCFAllocatorDefault, c, \
                                                kCFStringEncodingMacRoman); \
    CFShow(str); \
    CFRelease(str); \
  } while (false)

#else

#include "android/log.h"
#define DEBUG_TAG "ComboSample"
#define LOGI(...) \
    ((void)__android_log_print(ANDROID_LOG_INFO, DEBUG_TAG, __VA_ARGS__))

#endif // __APPLE__

#endif // LOGGING_H
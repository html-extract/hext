// Copyright 2018 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef HEXT_GCC7DIAGNOSTICS_H_INCLUDED
#define HEXT_GCC7DIAGNOSTICS_H_INCLUDED

/// @file
///   Declares HEXT_GCC7_IGNORE_DIAG_UNSAFE_LOOP and HEXT_GCC7_RESTORE_DIAG

#ifndef __CLANG__
  #ifdef __GNUC__
    #if __GNUC__ <= 7

/// GCC7 emits the following warning for range-based for loops:
///   warning: missed loop optimization, the loop counter may overflow
///   [-Wunsafe-loop-optimizations]
/// The warning may safely be ignored, because it's just a missed
/// optimization, and not actually unsafe.
#define HEXT_GCC7_IGNORE_DIAG_UNSAFE_LOOP \
  _Pragma("GCC diagnostic push") \
  _Pragma("GCC diagnostic ignored \"-Wunsafe-loop-optimizations\"")

/// Restore default diagnostic options
#define HEXT_GCC7_RESTORE_DIAG _Pragma("GCC diagnostic pop")

    #endif
  #endif
#endif

#ifndef HEXT_GCC7_IGNORE_DIAG_UNSAFE_LOOP
  #define HEXT_GCC7_IGNORE_DIAG_UNSAFE_LOOP
#endif
#ifndef HEXT_GCC7_RESTORE_DIAG
  #define HEXT_GCC7_RESTORE_DIAG
#endif

#endif // HEXT_GCC7DIAGNOSTICS_H_INCLUDED


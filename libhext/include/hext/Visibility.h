// Copyright 2016 Thomas Trapp
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

#ifndef HEXT_VISIBILITY_H_INCLUDED
#define HEXT_VISIBILITY_H_INCLUDED

/// @file
///   Defines HEXT_PUBLIC and HEXT_PRIVATE.


#if defined(__GNUC__) && !defined(_WIN32)
  #define HEXT_PUBLIC  __attribute__ ((visibility ("default")))
  #define HEXT_PRIVATE __attribute__ ((visibility ("hidden")))
#else
  #define HEXT_PUBLIC
  #define HEXT_PRIVATE
#endif


#endif // HEXT_VISIBILITY_H_INCLUDED


// Copyright 2015 Thomas Trapp
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

#ifndef HEXT_CAPTURE_FUNCTION_H_INCLUDED
#define HEXT_CAPTURE_FUNCTION_H_INCLUDED

/// @file
///   Declares hext::CaptureFunction

#include <functional>
#include <string>

#include <gumbo.h>


namespace hext {


/// A type of std::function that receives an HTML element and returns a string.
using CaptureFunction = std::function<std::string (const GumboNode *)>;


} // namespace hext


#endif // HEXT_CAPTURE_FUNCTION_H_INCLUDED


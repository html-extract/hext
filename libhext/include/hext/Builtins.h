// Copyright 2015, 2016 Thomas Trapp
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

#ifndef HEXT_BUILTINS_H_INCLUDED
#define HEXT_BUILTINS_H_INCLUDED

/// @file
///   Contains every predefined CaptureFunction.

#include "hext/CaptureFunction.h"
#include "hext/Visibility.h"


namespace hext {


/// A CaptureFunction that returns the text of an HTML element.
/// The intent is to mimic functions like jQuery's text(), IE's innerText() or
/// textContent().
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * node = ...; // <div> like<div>a</div>rolling  stone</div>
///   assert(TextBuiltin(node) == "like a rolling stone");
/// ~~~~~~~~~~~~~
///
/// @param node:  A pointer to a GumboNode.
/// @returns  A string containing the HTML element's text.
HEXT_PUBLIC extern const CaptureFunction TextBuiltin;


/// A CaptureFunction that returns the inner HTML of an HTML element.
/// The intent is to mimic innerHtml().
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * node = ...; // <div> like<div>a</div>rolling  stone</div>
///   assert(InnerHtmlBuiltin(node) == " like<div>a</div>rolling  stone");
/// ~~~~~~~~~~~~~
///
/// @param node:  A pointer to a GumboNode.
/// @returns  A string containing the HTML element's inner HTML.
HEXT_PUBLIC extern const CaptureFunction InnerHtmlBuiltin;


/// A CaptureFunction that returns the inner HTML of an HTML element without
/// tags.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * node = ...; // <div> like<div>a</div>rolling  stone</div>
///   assert(StripTagsBuiltin(node) == " likearolling  stone");
/// ~~~~~~~~~~~~~
///
/// @param node:  A pointer to a GumboNode.
/// @returns  A string containing the HTML element's inner HTML without tags.
HEXT_PUBLIC extern const CaptureFunction StripTagsBuiltin;


} // namespace hext


#endif // HEXT_BUILTINS_H_INCLUDED


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

#ifndef HEXT_PARSE_HEXT_H_INCLUDED
#define HEXT_PARSE_HEXT_H_INCLUDED

/// @file
///   Declares hext::ParseHext

#include "hext/Rule.h"
#include "hext/SyntaxError.h"
#include "hext/Visibility.h"

#include <cstddef>


namespace hext {


/// Parses a null-terminated string containing hext rule definitions.
/// Throws SyntaxError with a detailed error message on invalid input.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   try {
///     Rule rule = ParseHext("<a href:link />");
///   } catch( SyntaxError& e ) {
///     // e.what() will contain a detailed error message.
///   }
/// ~~~~~~~~~~~~~
///
/// @throws SyntaxError
///
/// @param hext:  A null-terminated string containing hext rule definitions.
/// @returns      The parsed Rule.
HEXT_PUBLIC Rule ParseHext(const char * hext);

/// Parses a buffer containing hext rule definitions.
/// Throws SyntaxError with a detailed error message on invalid input.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   std::string hext_str("<a href:link />");
///   try {
///     Rule rule = ParseHext(hext_str.c_str(), hext_str.size());
///     // ... do sth. with rule ...
///   } catch( SyntaxError& e ) {
///     // e.what() will contain a detailed error message.
///   }
/// ~~~~~~~~~~~~~
///
/// @throws SyntaxError
///
/// @param hext:  A string containing hext rule definitions.
/// @param size:  The length of the string.
/// @returns      The parsed Rule.
HEXT_PUBLIC Rule ParseHext(const char * hext, std::size_t size);


} // namespace hext


#endif // HEXT_PARSE_HEXT_H_INCLUDED


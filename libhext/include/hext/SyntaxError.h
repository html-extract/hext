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

#ifndef HEXT_SYNTAX_ERROR_H_INCLUDED
#define HEXT_SYNTAX_ERROR_H_INCLUDED

/// @file
///   Declares hext::SyntaxError

#include <stdexcept>
#include <string>


namespace hext {


/// The exception that is thrown when parsing invalid hext.
/// SyntaxError.what() will contain a detailed error message.
class SyntaxError : public std::runtime_error
{
public:
  explicit SyntaxError(const std::string& msg) noexcept;
};


} // namespace hext


#endif // HEXT_SYNTAX_ERROR_H_INCLUDED


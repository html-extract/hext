// Copyright 2021 Thomas Trapp
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

#ifndef HEXT_MAXSEARCH_ERROR_H_INCLUDED
#define HEXT_MAXSEARCH_ERROR_H_INCLUDED

/// @file
///   Declares hext::MaxSearchError

#include "hext/Visibility.h"

#include <stdexcept>
#include <string>


namespace hext {


/// The exception that is thrown when max_searches reaches zero while calling
/// `Rule::extract`.
class HEXT_PUBLIC MaxSearchError : public std::runtime_error
{
public:
  explicit MaxSearchError(const std::string& msg) noexcept
  : std::runtime_error(msg)  // noexcept
  {}
};


} // namespace hext


#endif // HEXT_MAXSEARCH_ERROR_H_INCLUDED


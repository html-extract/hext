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

#ifndef HEXT_PREPEND_PIPE_H_INCLUDED
#define HEXT_PREPEND_PIPE_H_INCLUDED

/// @file
///   Declares hext::PrependPipe

#include "hext/Cloneable.h"
#include "hext/StringPipe.h"
#include "hext/Visibility.h"

#include <string>


namespace hext {


/// Prepends a given string to a string.
class HEXT_PUBLIC PrependPipe final
  : public hext::Cloneable<PrependPipe, StringPipe>
{
public:
  /// Constructs a PrependPipe.
  ///
  /// @param  prefix:  The string to prepend.
  explicit PrependPipe(std::string prefix) noexcept;

  /// Prepends a given string to str.
  std::string transform(std::string str) const override;

private:
  std::string prefix_;
};


} // namespace hext


#endif // HEXT_PREPEND_PIPE_H_INCLUDED


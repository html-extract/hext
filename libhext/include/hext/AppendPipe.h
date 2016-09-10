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

#ifndef HEXT_APPEND_PIPE_H_INCLUDED
#define HEXT_APPEND_PIPE_H_INCLUDED

/// @file
///   Declares hext::AppendPipe

#include "hext/Cloneable.h"
#include "hext/StringPipe.h"
#include "hext/Visibility.h"

#include <string>


namespace hext {


/// Appends a given string to a string.
class HEXT_PUBLIC AppendPipe final
  : public hext::Cloneable<AppendPipe, StringPipe>
{
public:
  /// Constructs an AppendPipe.
  ///
  /// @param  suffix:  The string to append.
  explicit AppendPipe(std::string suffix);

  /// Appends a given string to str.
  std::string transform(std::string str) const override;

private:
  std::string suffix_;
};


} // namespace hext


#endif // HEXT_APPEND_PIPE_H_INCLUDED


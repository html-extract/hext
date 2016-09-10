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

#ifndef HEXT_TRIM_PIPE_H_INCLUDED
#define HEXT_TRIM_PIPE_H_INCLUDED

/// @file
///   Declares hext::TrimPipe

#include "hext/Cloneable.h"
#include "hext/StringPipe.h"
#include "hext/Visibility.h"

#include <string>


namespace hext {


/// Trims characters from the beginning and end of a string. Trims space by
/// default.
class HEXT_PUBLIC TrimPipe final : public hext::Cloneable<TrimPipe, StringPipe>
{
public:
  /// Constructs a TrimPipe.
  ///
  /// @param  trim_any_of:  Trim any of these characters from beginning or end
  ///                       of the string. Default: Trim spaces.
  explicit TrimPipe(std::string trim_any_of = " ");

  /// Removes all left and right characters that were given in the constructor
  /// from str.
  std::string transform(std::string str) const override;

private:
  std::string trim_any_of_;
};


} // namespace hext


#endif // HEXT_TRIM_PIPE_H_INCLUDED


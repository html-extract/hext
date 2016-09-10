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

#ifndef HEXT_CASE_PIPE_H_INCLUDED
#define HEXT_CASE_PIPE_H_INCLUDED

/// @file
///   Declares hext::CasePipe

#include "hext/Cloneable.h"
#include "hext/StringPipe.h"
#include "hext/Visibility.h"

#include <string>


namespace hext {


/// Changes the case of a string. Changes to lower case by default.
class HEXT_PUBLIC CasePipe final : public hext::Cloneable<CasePipe, StringPipe>
{
public:
  /// CasePipe's options.
  enum Option
  {
    ToLower = 1 << 1,
    ToUpper = 1 << 2
  };

  /// Constructs a CasePipe.
  ///
  /// @param option:  Change the string to this case. Default: to lower case.
  explicit CasePipe(Option option = Option::ToLower) noexcept;

  /// Changes the case of str.
  std::string transform(std::string str) const override;

private:
  Option option_;
};


} // namespace hext


#endif // HEXT_CASE_PIPE_H_INCLUDED


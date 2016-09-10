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

#ifndef HEXT_REGEX_REPLACE_PIPE_H_INCLUDED
#define HEXT_REGEX_REPLACE_PIPE_H_INCLUDED

/// @file
///   Declares hext::RegexReplacePipe

#include "hext/Cloneable.h"
#include "hext/StringPipe.h"
#include "hext/Visibility.h"

#include <string>

#include <boost/regex.hpp>


namespace hext {


/// Replaces a string within a string according to a given regex.
///
/// @par Example:
///   Use backreferences to address capture groups:
///   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///     RegexReplacePipe r(boost::regex("^(\\w+) (\\\w+)$"), "$2 $1");
///     r.transform("first second");    // "second first"
///   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class HEXT_PUBLIC RegexReplacePipe final
  : public hext::Cloneable<RegexReplacePipe, StringPipe>
{
public:
  /// Constructs a RegexReplacePipe.
  ///
  /// @param regex:  A regular expression that is applied to the string.
  /// @param   str:  The string that will replace the portion matching regex.
  RegexReplacePipe(boost::regex regex, std::string str);

  /// Replaces a string within str according to the regex given in the
  /// constructor.
  std::string transform(std::string str) const override;

private:
  boost::regex regex_;
  std::string replace_;
};


} // namespace hext


#endif // HEXT_REGEX_REPLACE_PIPE_H_INCLUDED


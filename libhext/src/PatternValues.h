// Copyright 2015-2017 Thomas Trapp
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

#ifndef HEXT_PATTERN_VALUES_H_INCLUDED
#define HEXT_PATTERN_VALUES_H_INCLUDED

#include "hext/CaptureFunction.h"
#include "hext/Match.h"
#include "hext/NegateMatch.h"
#include "hext/StringPipe.h"
#include "hext/ValueTest.h"

#include <memory>
#include <optional>
#include <string>
#include <utility>

#include <boost/regex.hpp>


namespace hext {


/// Holds all values required to create every Match and Capture when parsing
/// hext rule definitions.
struct PatternValues
{
  PatternValues();

  /// Consume generic ValueTest.
  template<typename ValueTestType, typename... Args>
  void set_test(Args&&... arg)
  {
    this->test = std::make_unique<ValueTestType>(std::forward<Args>(arg)...);
  }

  /// Consume generic Trait.
  template<typename MatchType, typename... Args>
  void set_trait(Args&&... arg)
  {
    this->trait = std::make_unique<MatchType>(std::forward<Args>(arg)...);
  }

  /// Add generic StringPipe.
  template<typename StringPipeType, typename... Args>
  void add_pipe(Args&&... arg)
  {
    if( this->pipe )
      this->pipe->emplace<StringPipeType>(std::forward<Args>(arg)...);
    else
      this->pipe = std::make_unique<StringPipeType>(std::forward<Args>(arg)...);
  }

  /// Reset all members to their original state.
  void reset();

  /// The current nth-pattern for NthChildMatch.
  std::pair<int, int> nth;

  /// The current builtin function.
  CaptureFunction builtin;

  /// The current attribute name.
  std::string attr_name;

  /// The current attribute literal value.
  std::string literal_value;

  /// The current Capture's result name.
  std::string cap_var;

  /// The current Capture's StringPipe.
  std::unique_ptr<StringPipe> pipe;

  /// The current Match's regex.
  /// std::optional is used to be able to distinguish between empty regex
  /// and no regex.
  std::optional<boost::regex> regex;

  /// The current ValueTest.
  std::unique_ptr<ValueTest> test;

  /// The current Trait.
  std::unique_ptr<Match> trait;

  /// The current NegateMatch.
  std::unique_ptr<NegateMatch> negate;

  /// The current regex options.
  boost::regex::flag_type regex_flag;

  /// Whether the current Capture is optional.
  bool optional;
};


} // namespace hext


#endif // HEXT_PATTERN_VALUES_H_INCLUDED


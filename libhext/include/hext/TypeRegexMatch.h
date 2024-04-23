// Copyright 2024 Thomas Trapp
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

#ifndef HEXT_TYPE_REGEX_MATCH_H_INCLUDED
#define HEXT_TYPE_REGEX_MATCH_H_INCLUDED

/// @file
///   Declares hext::TypeRegexMatch

#include "hext/Cloneable.h"
#include "hext/Match.h"
#include "hext/Visibility.h"

#include <boost/regex.hpp>
#include <gumbo.h>


namespace hext {


/// Matches the name of an HTML element against a regular expression.
class HEXT_PUBLIC TypeRegexMatch final : public Cloneable<TypeRegexMatch, Match>
{
public:
  /// Constructs a TypeRegexMatch.
  ///
  /// @param regex:  The regular expression that is applied against a tag name.
  explicit TypeRegexMatch(boost::regex regex);

  /// Returns true if the node has a tag name which matches the given regex.
  ///
  /// @param node:  A pointer to a GumboNode.
  bool matches(const GumboNode * node) const override;

private:
  /// The regex an HTML Elelement's tag name has to match.
  boost::regex rx_;
};


} // namespace hext


#endif // HEXT_TYPE_REGEX_MATCH_H_INCLUDED


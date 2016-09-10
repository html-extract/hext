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

#ifndef HEXT_MATCH_H_INCLUDED
#define HEXT_MATCH_H_INCLUDED

/// @file
///   Declares hext::Match

#include "hext/Visibility.h"

#include <memory>

#include <gumbo.h>


namespace hext {


/// Abstract base for every Match.
///
/// Matches are applied to HTML nodes with Match::matches() which will
/// return true if the HTML node matches.
///
/// Note: You probably don't want to inherit from this class directly, unless
///       you want to provide your own Match::clone() method. If your subclass
///       has a copy constructor, you can extend from
///       hext::Cloneable<YourSubclass, hext::Match> which provides a generic
///       clone method.
class HEXT_PUBLIC Match
{
public:
  Match() noexcept = default;
  Match(const Match&) = default;
  Match(Match&&) noexcept = default;
  Match& operator=(const Match&) = default;
  Match& operator=(Match&&) noexcept = default;
  virtual ~Match() noexcept = default;

  /// Clones derived object.
  virtual std::unique_ptr<Match> clone() const = 0;

  /// Returns true if this Match matches node.
  virtual bool matches(const GumboNode * node) const = 0;
};


} // namespace hext


#endif // HEXT_MATCH_H_INCLUDED


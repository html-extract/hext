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

#ifndef HEXT_ONLY_CHILD_MATCH_H_INCLUDED
#define HEXT_ONLY_CHILD_MATCH_H_INCLUDED

/// @file
///   Declares hext::OnlyChildMatch

#include "hext/Cloneable.h"
#include "hext/Match.h"
#include "hext/Visibility.h"

#include <gumbo.h>


namespace hext {


/// Matches HTML nodes that are the only child of their parent HTML element.
///
/// The intent is to mimic the CSS pseudo-classes only-child and
/// only-child-of-type.
///
/// See https://developer.mozilla.org/en-US/docs/Web/CSS/:only-child
class HEXT_PUBLIC OnlyChildMatch final : public Cloneable<OnlyChildMatch, Match>
{
public:
  /// OnlyChildMatch's options.
  enum Option
  {
    /// Count siblings of any type (:only-child).
    AnyType = 1 << 1,

    /// Only count siblings of the same type (:only-child-of-type).
    OfType  = 1 << 2
  };

  /// Constructs an OnlyChildMatch.
  ///
  /// @param options:  See OnlyChildMatch::Option.
  ///                  Default: Count any element (:only-child).
  explicit OnlyChildMatch(Option options = Option::AnyType) noexcept;

  /// Returns true if node is the only child of its parent.
  bool matches(const GumboNode * node) const noexcept override;

private:
  /// See OnlyChildMatch::Option.
  Option options_;
};


/// Applies Bitwise-OR to OnlyChildMatch::Option.
HEXT_PUBLIC inline OnlyChildMatch::Option
operator|(OnlyChildMatch::Option left, OnlyChildMatch::Option right) noexcept
{
  return static_cast<OnlyChildMatch::Option>(static_cast<int>(left) |
                                             static_cast<int>(right));
}


/// Applies Bitwise-AND to OnlyChildMatch::Option.
HEXT_PUBLIC inline OnlyChildMatch::Option
operator&(OnlyChildMatch::Option left, OnlyChildMatch::Option right) noexcept
{
  return static_cast<OnlyChildMatch::Option>(static_cast<int>(left) &
                                             static_cast<int>(right));
}


} // namespace hext


#endif // HEXT_ONLY_CHILD_MATCH_H_INCLUDED


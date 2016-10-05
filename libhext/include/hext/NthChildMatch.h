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

#ifndef HEXT_NTH_CHILD_MATCH_H_INCLUDED
#define HEXT_NTH_CHILD_MATCH_H_INCLUDED

/// @file
///   Declares hext::NthChildMatch

#include "hext/Cloneable.h"
#include "hext/Match.h"
#include "hext/HtmlTag.h"
#include "hext/Visibility.h"

#include <utility>

#include <gumbo.h>


namespace hext {


/// Matches HTML nodes having a certain position within their parent HTML
/// element.
///
/// The intent is to mimic the following CSS pseudo-classes:
///   nth-child,   nth-of-type, nth-last-of-type, first-of-type, last-of-type,
///   first-child, last-child,  nth-last-child,   nth-last-of-type
///
/// See https://developer.mozilla.org/en-US/docs/Web/CSS/%3Anth-child for a
/// detailed explanation.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   // Assume first, second, third are children of the following <ul> element:
///   // <ul><li>1</li><li>2</li><li>3</li></ul>
///   const GumboNode * first  = ...;
///   const GumboNode * second = ...;
///   const GumboNode * third  = ...;
///
///   NthChildMatch m_even(2, 0); // :nth-child(2n)
///   NthChildMatch m_odd (2, 1); // :nth-child(2n+1)
///
///   assert(!m_even.matches(first));
///   assert( m_even.matches(second));
///   assert(!m_even.matches(third));
///
///   assert( m_odd.matches(first));
///   assert(!m_odd.matches(second));
///   assert( m_odd.matches(third));
/// ~~~~~~~~~~~~~
///
/// @par last-of-type Example:
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~
///   // Assume first, second, third are children of the following <a> element:
///   // <a>
///   //   <b>1</b>
///   //   <u>2</u>
///   //   <b>3</b>
///   // </a>
///   const GumboNode * first  = ...;
///   const GumboNode * second = ...;
///   const GumboNode * third  = ...;
///
///   NthChildMatch m_last_of_type(
///     0,                        // no repetition
///     1,                        // last element
///     NthChildMatch::Last |     // count following siblings and
///       NthChildMatch::OfType   // only count elements with
///                               // same tag.
///   );
///
///   assert(!m_last_of_type.matches(first));
///   assert( m_last_of_type.matches(second));
///   assert( m_last_of_type.matches(third));
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~
class HEXT_PUBLIC NthChildMatch final : public Cloneable<NthChildMatch, Match>
{
public:
  /// NthChildMatch's options.
  enum Option
  {
    /// Count preceding siblings (:nth-child).
    First  = 1 << 1,

    /// Count following siblings (:nth-last-child).
    Last   = 1 << 2,

    /// Only count siblings of the same type (:nth-of-type).
    OfType = 1 << 3
  };

  /// Constructs an NthChildMatch with the pattern <step * n + shift>.
  ///
  /// @param    step:  The step of the pattern.
  /// @param   shift:  The shift of the pattern.
  /// @param options:  See NthChildMatch::Option.
  ///                  Default: Count any preceding HTML element.
  NthChildMatch(int    step,
                int    shift,
                Option options = Option::First) noexcept;

  /// Constructs an NthChildMatch with the pattern <step * n + shift>, where
  /// step and shift is given as a std::pair.
  ///
  /// @param step_and_shift:  The step and shift of the pattern.
  /// @param        options:  See NthChildMatch::Option.
  ///                         Default: Count any preceding HTML element.
  explicit NthChildMatch(std::pair<int, int> step_and_shift,
                         Option              options = Option::First) noexcept;

  /// Returns true if HTML node matches pattern <step * n + shift>.
  ///
  /// @param node:  A pointer to a GumboNode.
  bool matches(const GumboNode * node) const noexcept override;

private:
  /// Count preceding siblings of an HTML node.
  ///
  /// @param      node:  A pointer to a GumboNode.
  /// @param count_tag:  If given any value other than HtmlTag::ANY, only count
  ///                    siblings having this HtmlTag.
  HEXT_PRIVATE
    int count_preceding_siblings(const GumboNode * node,
                                 HtmlTag           count_tag) const noexcept;

  /// Count following siblings of an HTML node.
  ///
  /// @param      node:  A pointer to a GumboNode.
  /// @param count_tag:  If given any value other than HtmlTag::ANY, only count
  ///                    siblings having this HtmlTag.
  HEXT_PRIVATE
    int count_following_siblings(const GumboNode * node,
                                 HtmlTag           count_tag) const noexcept;

  /// The step in the pattern <step * n + shift>
  int step_;

  /// The shift in the pattern <step * n + shift>
  int shift_;

  /// See NthChildMatch::Option.
  Option options_;
};


/// Applies Bitwise-OR to NthChildMatch::Option.
HEXT_PUBLIC inline NthChildMatch::Option
operator|(NthChildMatch::Option left, NthChildMatch::Option right) noexcept
{
  return static_cast<NthChildMatch::Option>(static_cast<int>(left) |
                                            static_cast<int>(right));
}


/// Applies Bitwise-AND to NthChildMatch::Option.
HEXT_PUBLIC inline NthChildMatch::Option
operator&(NthChildMatch::Option left, NthChildMatch::Option right) noexcept
{
  return static_cast<NthChildMatch::Option>(static_cast<int>(left) &
                                            static_cast<int>(right));
}


} // namespace hext


#endif // HEXT_NTH_CHILD_MATCH_H_INCLUDED


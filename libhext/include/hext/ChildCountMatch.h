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

#ifndef HEXT_CHILD_COUNT_MATCH_H_INCLUDED
#define HEXT_CHILD_COUNT_MATCH_H_INCLUDED

/// @file
///   Declares hext::ChildCountMatch

#include "hext/Cloneable.h"
#include "hext/Match.h"
#include "hext/Visibility.h"

#include <gumbo.h>


namespace hext {


/// Matches HTML elements that have a certain amount of children of type
/// element (excluding text nodes, document nodes and others).
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * none = ...; // <div>Text nodes are ignored</div>
///   GumboNode * two  = ...; // <ul><li>first</li><li>last</li></ul>
///
///   ChildCountMatch m_none(/* child count */ 0);
///   ChildCountMatch m_two (/* child count */ 2);
///
///   assert( m_none.matches(none));
///   assert(!m_none.matches(two));
///
///   assert( m_two.matches(two));
///   assert(!m_two.matches(none));
/// ~~~~~~~~~~~~~
class HEXT_PUBLIC ChildCountMatch final
  : public Cloneable<ChildCountMatch, Match>
{
public:
  /// Construct a ChildCountMatch that matches HTML elements with a child_count
  /// amount of children.
  explicit ChildCountMatch(unsigned int child_count) noexcept;

  /// Return true if node has child_count amount of children.
  ///
  /// @param node:  A pointer to a GumboNode of type GUMBO_NODE_ELEMENT.
  bool matches(const GumboNode * node) const noexcept override;

private:
  /// Return amount of node's children that have node type GUMBO_NODE_ELEMENT.
  HEXT_PRIVATE
    unsigned int count_child_elements(const GumboNode * node) const noexcept;

  /// The amount of children an HTML element must have in order to match.
  unsigned int child_count_;
};


} // namespace hext


#endif // HEXT_CHILD_COUNT_MATCH_H_INCLUDED


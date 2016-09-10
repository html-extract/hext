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

#ifndef HEXT_ATTRIBUTE_COUNT_MATCH_H_INCLUDED
#define HEXT_ATTRIBUTE_COUNT_MATCH_H_INCLUDED

/// @file
///   Declares hext::AttributeCountMatch

#include "hext/Cloneable.h"
#include "hext/Match.h"
#include "hext/Visibility.h"

#include <gumbo.h>


namespace hext {


/// Matches HTML elements that have a certain amount of HTML attributes.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * no_attrs  = ...; // <hr/>
///   GumboNode * two_attrs = ...; // <img class="picture" src="mona-lisa.jpg"/>
///
///   AttributeCountMatch m_no_attr (/* attribute count */ 0);
///   AttributeCountMatch m_two_attr(/* attribute count */ 2);
///
///   assert(m_no_attr.matches(no_attrs));
///   assert(m_two_attr.matches(two_attrs));
///
///   assert(!m_two_attr.matches(no_attrs));
///   assert(!m_no_attr.matches(two_attrs));
/// ~~~~~~~~~~~~~
class HEXT_PUBLIC AttributeCountMatch final
  : public Cloneable<AttributeCountMatch, Match>
{
public:
  /// Constructs an AttributeCountMatch that matches HTML elements that have a
  /// certain amount of HTML attributes.
  ///
  /// @param attribute_count:  The amount of HTML attributes a node must have
  ///                          in order to match.
  explicit AttributeCountMatch(unsigned int attribute_count) noexcept;

  /// Returns true if node has exactly attribute_count amount of HTML
  /// attributes.
  ///
  /// @param node:  A pointer to a GumboNode of type GUMBO_NODE_ELEMENT.
  bool matches(const GumboNode * node) const noexcept override;

private:
  /// The amount of HTML attributes an HTML element must have in order to match.
  unsigned int attribute_count_;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_COUNT_MATCH_H_INCLUDED


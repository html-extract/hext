#ifndef HEXT_ATTRIBUTE_COUNT_MATCH_H_INCLUDED
#define HEXT_ATTRIBUTE_COUNT_MATCH_H_INCLUDED

/// @file
///   Declares hext::AttributeCountMatch

#include "hext/Match.h"

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
class AttributeCountMatch : public Match
{
public:
  /// Constructs an AttributeCountMatch that matches HTML elements that have a
  /// certain amount of HTML attributes.
  ///
  /// @param attribute_count:  The amount of HTML attributes a node must have
  ///                          in order to match.
  explicit AttributeCountMatch(unsigned int attribute_count);

  /// Returns true if node has exactly attribute_count amount of HTML
  /// attributes.
  ///
  /// @param node:  A pointer to a GumboNode of type GUMBO_NODE_ELEMENT.
  bool matches(const GumboNode * node) const final;

private:
  /// The amount of HTML attributes an HTML element must have in order to match.
  unsigned int attribute_count_;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_COUNT_MATCH_H_INCLUDED


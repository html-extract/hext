#ifndef HEXT_CHILD_COUNT_MATCH_H_INCLUDED
#define HEXT_CHILD_COUNT_MATCH_H_INCLUDED

/// @file
///   Declares hext::ChildCountMatch

#include "hext/Match.h"

#include <gumbo.h>


namespace hext {


/// Matches HTML elements that have a certain amount of children of type
/// element (exluding text nodes, document nodes and others).
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
class ChildCountMatch : public Match
{
public:
  /// Construct a ChildCountMatch that matches HTML elements with a child_count
  /// amount of children.
  explicit ChildCountMatch(unsigned int child_count) noexcept;

  /// Return true if node has child_count amount of children.
  ///
  /// @param node:  A pointer to a GumboNode of type GUMBO_NODE_ELEMENT.
  bool matches(const GumboNode * node) const noexcept final;

private:
  /// Return amount of node's children that have node type GUMBO_NODE_ELEMENT.
  unsigned int count_child_elements(const GumboNode * node) const noexcept;

  /// The amount of children an HTML element must have in order to match.
  unsigned int child_count_;
};


} // namespace hext


#endif // HEXT_CHILD_COUNT_MATCH_H_INCLUDED


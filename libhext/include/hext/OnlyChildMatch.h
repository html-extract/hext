#ifndef HEXT_ONLY_CHILD_MATCH_H_INCLUDED
#define HEXT_ONLY_CHILD_MATCH_H_INCLUDED

#include "hext/Match.h"

#include <gumbo.h>


namespace hext {


/// Matches HTML nodes that are the only child of their parent HTML element.
///
/// The intent is to mimic the CSS pseudo-classes only-child.
///
/// See https://developer.mozilla.org/en-US/docs/Web/CSS/:only-child
class OnlyChildMatch : public Match
{
public:
  /// Returns true if node is the only child of its parent.
  bool matches(const GumboNode * node) const final;
};


} // namespace hext


#endif // HEXT_ONLY_CHILD_MATCH_H_INCLUDED


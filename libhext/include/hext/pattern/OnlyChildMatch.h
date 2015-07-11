#ifndef HEXT_PATTERN_ONLY_CHILD_MATCH_H_INCLUDED
#define HEXT_PATTERN_ONLY_CHILD_MATCH_H_INCLUDED

#include "hext/pattern/Match.h"

#include <gumbo.h>


namespace hext {


/// Matches if a node is the only child of its parent.
class OnlyChildMatch : public Match
{
public:
  /// Return true if node is the only child of its parent.
  bool matches(const GumboNode * node) const final;
};


} // namespace hext


#endif // HEXT_PATTERN_ONLY_CHILD_MATCH_H_INCLUDED


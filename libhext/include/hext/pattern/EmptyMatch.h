#ifndef HEXT_PATTERN_EMPTY_MATCH_H_INCLUDED
#define HEXT_PATTERN_EMPTY_MATCH_H_INCLUDED

#include "hext/pattern/MatchPattern.h"

#include <gumbo.h>


namespace hext {


/// An EmptyMatch is a MatchPattern that matches nodes that have no children
/// (including text-nodes).
class EmptyMatch : public MatchPattern
{
public:
  /// Return MatchResult<true, nullptr> if node has no children. Second member
  /// is always nullptr.
  MatchResult matches(const GumboNode * node) const final;
};


} // namespace hext


#endif // HEXT_PATTERN_EMPTY_MATCH_H_INCLUDED


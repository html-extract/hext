#ifndef HEXT_PATTERN_CHILD_COUNT_MATCH_H_INCLUDED
#define HEXT_PATTERN_CHILD_COUNT_MATCH_H_INCLUDED

#include "hext/pattern/MatchPattern.h"
#include "hext/NodeUtil.h"

#include <gumbo.h>


namespace hext {


/// A ChildCountMatch is a MatchPattern that matches nodes that have a certain
/// amount of children (exluding text-nodes).
class ChildCountMatch : public MatchPattern
{
public:
  /// Construct a ChildCountMatch that matches nodes with a child_count amount
  /// of children. If child_count is negative, child_count will be set to zero.
  explicit ChildCountMatch(int child_count);

  /// Return true if node has child_count amount of children.
  bool matches(const GumboNode * node) const final;

private:
  int child_count_;
};


} // namespace hext


#endif // HEXT_PATTERN_CHILD_COUNT_MATCH_H_INCLUDED


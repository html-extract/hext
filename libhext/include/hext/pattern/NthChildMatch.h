#ifndef HEXT_PATTERN_NTHCHILD_MATCH_H_INCLUDED
#define HEXT_PATTERN_NTHCHILD_MATCH_H_INCLUDED

#include "hext/pattern/MatchPattern.h"
#include "hext/NodeUtil.h"

#include <gumbo.h>


namespace hext {


/// An NthChildMatch is a MatchPattern that matches if a node's position within
/// its parent node is in set {step * n + shift}.
class NthChildMatch : public MatchPattern
{
public:
  /// Flag to specify how to determine a node's position within its parent.
  enum OffsetOf
  {
    /// Start counting from the first child.
    Front = 1 << 0,
    /// Start counting from the last child.
    Back  = 1 << 1
  };

  /// Construct an NthChildMatch that matches if a node's position within its
  /// parent node is in set {step * n + shift}. offset_of specifies the
  /// direction from which to start counting: OffsetOf::Front starts counting
  /// from the first child (default), OffsetOf::Back counts backwards from the
  /// last child. If count_tag is not GUMBO_TAG_UNKNOWN only count nodes that
  /// have a tag equal to count_tag.
  NthChildMatch(
    int step,
    int shift,
    GumboTag count_tag = GUMBO_TAG_UNKNOWN,
    OffsetOf offset_of = OffsetOf::Front
  );

  /// Return MatchResult(true, nullptr) if node matches. Second member is
  /// always nullptr.
  MatchResult matches(const GumboNode * node) const final;

private:
  const int step_;
  const int shift_;
  const GumboTag count_tag_;
  const OffsetOf offset_of_;
};


} // namespace hext


#endif // HEXT_PATTERN_NTHCHILD_MATCH_H_INCLUDED


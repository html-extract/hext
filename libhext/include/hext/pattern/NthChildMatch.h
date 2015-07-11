#ifndef HEXT_PATTERN_NTHCHILD_MATCH_H_INCLUDED
#define HEXT_PATTERN_NTHCHILD_MATCH_H_INCLUDED

#include "hext/pattern/MatchPattern.h"
#include "hext/HtmlTag.h"

#include <utility>

#include <gumbo.h>


namespace hext {


/// Match if a node's position within its parent node matches
/// pattern step*n+shift.
class NthChildMatch : public MatchPattern
{
public:
  /// Flag to specify how to determine a node's position within its parent.
  enum OffsetOf
  {
    /// Start counting from the first child.
    Front = 0,
    /// Start counting from the last child.
    Back
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
    OffsetOf offset_of = OffsetOf::Front,
    HtmlTag count_tag = HtmlTag::ANY
  );

  /// Construct an NthChildMatch with step and shift given as std::pair.
  explicit NthChildMatch(
    std::pair<int, int> step_and_shift,
    OffsetOf offset_of = OffsetOf::Front,
    HtmlTag count_tag = HtmlTag::ANY
  );

  /// Return true if node matches.
  bool matches(const GumboNode * node) const final;

private:
  /// Get the position of `node` within its parent. Only count nodes of type
  /// `GUMBO_NODE_ELEMENT`. First node has position 1. Return 0 if no parent.
  /// If `count_tag` is set to `GUMBO_TAG_UNKNOWN` all nodes are counted,
  /// regardless of their tag name. If any other `GumboTag` is passed, count
  /// only nodes that have a tag equal to `count_tag`.
  int count_preceding_siblings(
    const GumboNode * node,
    HtmlTag count_tag
  ) const;

  /// Get the position of `node` within its parent in reverse. Only count nodes
  /// of type `GUMBO_NODE_ELEMENT`. Last node has position 1. Return 0 if no
  /// parent. If `count_tag` is set to `GUMBO_TAG_UNKNOWN` all nodes are
  /// counted, regardless of their tag name. If any other `GumboTag` is passed,
  /// count only nodes that have tag equal to `count_tag`.
  int count_following_siblings(
    const GumboNode * node,
    HtmlTag count_tag
  ) const;

  int step_;
  int shift_;
  OffsetOf offset_of_;
  HtmlTag count_tag_;
};


} // namespace hext


#endif // HEXT_PATTERN_NTHCHILD_MATCH_H_INCLUDED


#ifndef HEXT_PATTERN_NTHCHILD_MATCH_H_INCLUDED
#define HEXT_PATTERN_NTHCHILD_MATCH_H_INCLUDED

#include "hext/pattern/MatchPattern.h"
#include "hext/NodeUtil.h"

#include <gumbo.h>


namespace hext {


/// An NthChildMatch is a MatchPattern that matches if a node's index within
/// its parent node is in set {step * n + shift}.
class NthChildMatch : public MatchPattern
{
public:
  /// Construct an NthChildMatch that matches if a node's index within its
  /// parent node is in set {step * n + shift}.
  NthChildMatch(int step, int shift);

  /// Return MatchResult(true, nullptr) if node matches. Second member is
  /// always nullptr.
  MatchResult matches(const GumboNode * node) const final;

private:
  const int step_;
  const int shift_;
};


} // namespace hext


#endif // HEXT_PATTERN_NTHCHILD_MATCH_H_INCLUDED


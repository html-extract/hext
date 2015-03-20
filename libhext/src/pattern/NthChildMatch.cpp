#include "hext/pattern/NthChildMatch.h"


namespace hext {


NthChildMatch::NthChildMatch(int step, int shift)
: step_(step)
, shift_(shift)
{
}

MatchResult NthChildMatch::matches(const GumboNode * node) const
{
  int node_pos = GetNodePositionWithinParent(node);
  if( this->step_ )
    return MatchResult(
      node_pos % this->step_ == this->shift_ % this->step_,
      nullptr
    );
  else
    return MatchResult(node_pos == this->shift_, nullptr);
}


} // namespace hext


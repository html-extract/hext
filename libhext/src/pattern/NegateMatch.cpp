#include "hext/pattern/NegateMatch.h"


namespace hext {


NegateMatch::NegateMatch()
: match_patterns_()
{
}

void NegateMatch::take_match_pattern(std::unique_ptr<MatchPattern>&& pattern)
{
  this->match_patterns_.push_back(std::move(pattern));
}

bool NegateMatch::matches(const GumboNode * node) const
{
  assert(node);
  if( !node )
    return false;

  for(const auto& mp : this->match_patterns_)
  {
    if( mp->matches(node) )
      return false;
  }

  return true;
}


} // namespace hext


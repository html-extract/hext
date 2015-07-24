#include "hext/NegateMatch.h"

#include <cassert>
#include <utility>


namespace hext {


NegateMatch::NegateMatch(
    std::vector<std::unique_ptr<Match>>&& v_matches) noexcept
: matches_(std::move(v_matches))  // noexcept
{
}

NegateMatch::NegateMatch(std::unique_ptr<Match>&& match)
: matches_()
{
  this->matches_.push_back(std::move(match));
}

void NegateMatch::take_match(std::unique_ptr<Match>&& match)
{
  this->matches_.push_back(std::move(match));
}

bool NegateMatch::matches(const GumboNode * node) const
{
  assert(node);
  if( !node )
    return true;

  for(const auto& match : this->matches_)
    if( match && match->matches(node) )
      return false;

  return true;
}


} // namespace hext


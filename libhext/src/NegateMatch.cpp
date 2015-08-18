#include "hext/NegateMatch.h"

#include <algorithm>
#include <cassert>
#include <utility>


namespace hext {


NegateMatch::NegateMatch(
    std::vector<std::unique_ptr<Match>> v_matches) noexcept
: matches_(std::move(v_matches))  // noexcept
{
}

NegateMatch::NegateMatch(std::unique_ptr<Match> match)
: matches_()
{
  this->matches_.push_back(std::move(match));
}

NegateMatch::~NegateMatch() = default;
NegateMatch::NegateMatch(NegateMatch&&) = default;

NegateMatch::NegateMatch(const NegateMatch& other)
: matches_()
{
  this->matches_.reserve(other.matches_.size());
  for(const auto& m : other.matches_)
    this->matches_.emplace_back(m ? m->clone() : nullptr);
}

NegateMatch& NegateMatch::operator=(NegateMatch&&) = default;

NegateMatch& NegateMatch::operator=(const NegateMatch& other)
{
  using std::swap;
  NegateMatch tmp(other);
  swap(*this, tmp);
  return *this;
}

void NegateMatch::append_match(std::unique_ptr<Match> match)
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


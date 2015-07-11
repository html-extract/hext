#include "hext/Rule.h"

#include "MatchContext.h"


namespace hext {


MatchContext::MatchContext(
  rule_it rule_begin,
  rule_it rule_end,
  const GumboVector& nodes
)
: r_begin_(rule_begin),
  r_end_(rule_end),
  nodes_(nodes),
  n_(0),
  n_len_(nodes.length)
{
}

boost::optional<MatchContext::match_group> MatchContext::match_next()
{
  assert(this->r_begin_ <= this->r_end_);
  if( this->r_begin_ == this->r_end_ )
    return {};

  assert(this->n_ <= this->n_len_);
  if( this->n_ == this->n_len_ )
    return {};

  match_group mg;
  auto rule = this->r_begin_;
  while( rule != this->r_end_ && this->n_ < this->n_len_ )
  {
    if( rule->is_optional() )
    {
      // Optional rules can be matched anywhere up to the next match of a
      // mandatory rule
      auto stop_rule = this->find_mandatory_rule(rule);
      assert(rule != stop_rule);

      // If there are no mandatory rules, match until end
      if( stop_rule == this->r_end_ )
      {
        this->match_to_node(mg, rule, stop_rule, this->n_len_);
        if( mg.size() )
        {
          return mg;
        }
        else
        {
          // If there wasn't matched anything now, there won't be later matches
          this->n_ = this->n_len_;
          return {};
        }
      }
      else
      {
        // Find the matching node of the next mandatory rule
        auto stop_node = this->find_match(this->n_, this->n_len_, *stop_rule);

        // If the stop_rule is not included in this match_group
        if( stop_rule < rule )
        {
          // match until the last rule
          this->match_to_node(mg, rule, this->r_end_, stop_node);
          // If there was no match found for the mandatory rule, then don't
          // search for it in the next call to match_next()
          if( stop_node == this->n_len_ )
            this->n_ = this->n_len_;
          return mg;
        }
        // If stop_rule wasn't found, abort (stop_rule is mandatory)
        else if( stop_node == this->n_len_ )
        {
          this->n_ = this->n_len_;
          return {};
        }
        // If stop_rule is included in this match_group
        else
        {
          this->match_to_node(mg, rule, stop_rule, stop_node);
          // Also include the already matched stop_rule
          this->push_match_pair(mg, stop_rule, stop_node);
          rule = stop_rule + 1;
          this->n_ = stop_node + 1;
        }
      }
    }
    else // rule is mandatory
    {
      this->n_ = this->find_match(this->n_, this->n_len_, *rule);

      // If a mandatory rule isn't found, abort immediately
      if( this->n_ == this->n_len_ )
        return {};

      this->push_match_pair(mg, rule, this->n_);
      ++this->n_;
      ++rule;
    }

    assert(this->n_ <= this->n_len_);
    assert(this->r_begin_ <= this->r_end_);
  }

  // Optional rules can be skipped
  while( rule != this->r_end_ && rule->is_optional() )
    ++rule;

  if( rule == this->r_end_ )
    return mg;

  this->n_ = this->n_len_;
  return {};
}

MatchContext::rule_it MatchContext::find_mandatory_rule(rule_it it) const
{
  assert(it >= this->r_begin_ && it <= this->r_end_);

  auto pred = [](const Rule& r) {
    return !r.is_optional();
  };

  auto result = std::find_if(it, this->r_end_, pred);
  if( result != this->r_end_ )
    return result;

  result = std::find_if(this->r_begin_, it, pred);
  return ( result == it ? this->r_end_ : result );
}

unsigned int MatchContext::find_match(
  unsigned int begin,
  unsigned int end,
  const Rule& rule
) const
{
  assert(begin <= end);

  for(; begin != end; ++begin)
  {
    auto node = static_cast<const GumboNode *>(this->nodes_.data[begin]);
    if( rule.matches(node) )
      return begin;
  }

  return end;
}

void MatchContext::match_to_node(
  match_group& mg,
  rule_it rule,
  rule_it stop_rule,
  unsigned int stop_node
)
{
  assert(rule >= this->r_begin_ && rule < this->r_end_);
  assert(rule < stop_rule);
  assert(stop_rule >= this->r_begin_ && stop_rule <= this->r_end_);
  assert(stop_node >= this->n_ && stop_node <= this->n_len_);

  while( this->n_ < stop_node && rule != stop_rule )
  {
    auto matching_node = this->find_match(this->n_, stop_node, *rule);
    if( matching_node < stop_node )
    {
      this->push_match_pair(mg, rule, matching_node);
      this->n_ = matching_node + 1;
    }
    ++rule;
  }
}

void MatchContext::push_match_pair(
  match_group& mg,
  rule_it rule,
  unsigned int n
) const
{
  assert(rule != this->r_end_);
  assert(n < this->n_len_);
  mg.push_back(std::make_pair(
    &(*rule),
    static_cast<const GumboNode *>(this->nodes_.data[n])
  ));
}


} // namespace hext


#include "hext/MatchContext.h"
#include "hext/Rule.h"


namespace hext {


MatchContext::MatchContext(
  rule_iter rule_begin,
  rule_iter rule_end,
  const GumboVector * nodes,
  unsigned int nodes_length
)
: r_begin_(rule_begin),
  r_end_(rule_end),
  r_manda_cnt_(
    std::count_if(
      rule_begin,
      rule_end,
      [](const Rule& r) { return !r.optional(); }
    )
  ),
  nodes_(nodes),
  nodes_length_(nodes_length),
  current_node_(0)
{
}

boost::optional<MatchContext::match_group> MatchContext::match_next()
{
  if( this->r_begin_ == this->r_end_ )
    return boost::optional<MatchContext::match_group>();

  if( !this->nodes_ || !this->nodes_length_ )
    return boost::optional<MatchContext::match_group>();

  if( this->current_node_ >= this->nodes_length_ )
    return boost::optional<MatchContext::match_group>();

  auto rule = this->r_begin_;
  unsigned int manda_match_cnt = 0;
  MatchContext::match_group mg;
  while( this->current_node_ < this->nodes_length_ )
  {
    assert(this->current_node_ < this->nodes_length_);
    auto node = static_cast<const GumboNode *>(
      this->nodes_->data[this->current_node_]
    );
    assert(node);

    bool skip = false;
    if( rule->optional() )
    {
      // Prefer matching mandatory rules to optional rules
      auto next_mandatory = this->next_mandatory_rule(rule);
      if( next_mandatory != this->r_end_ && next_mandatory->matches(node) )
      {
        // Check if the next mandatory rule is in the next result set
        if( next_mandatory <= rule )
        {
          return this->match_next();
        }
        else
        {
          ++manda_match_cnt;
          rule = next_mandatory + 1;
          mg.push_back(std::make_pair(&(*rule), node));
          skip = true;
        }
      }
    }

    if( !skip && rule->matches(node) )
    {
      if( !rule->optional() )
        ++manda_match_cnt;
      mg.push_back(std::make_pair(&(*rule), node));
      rule++;
    }

    this->current_node_++;

    if( rule == this->r_end_ )
    {
      if( manda_match_cnt >= this->r_manda_cnt_ )
        return mg;
      else
        return this->match_next();
    }
  }

  while( rule != this->r_end_ && rule->optional() )
    rule++;

  if( rule == this->r_end_ && manda_match_cnt >= this->r_manda_cnt_ )
    return mg;

  return boost::optional<MatchContext::match_group>();
}

MatchContext::rule_iter MatchContext::next_mandatory_rule(rule_iter it) const
{
  assert(it >= this->r_begin_ && it <= this->r_end_);

  auto pred = [](const Rule& r) {
    return !r.optional();
  };

  if( it == this->r_end_ )
    it = this->r_begin_;
  else
    ++it;

  auto result = std::find_if(it, this->r_end_, pred);
  if( result != this->r_end_ )
    return result;

  result = std::find_if(this->r_begin_, it, pred);
  if( result == it )
    return this->r_end_;
  else
    return result;
}


} // namespace hext


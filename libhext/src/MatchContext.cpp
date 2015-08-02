#include "MatchContext.h"

#include "hext/Rule.h"
#include "NodeUtil.h"


namespace hext {


MatchContext::MatchContext(const Rule * rule,
                           const GumboNode * node) noexcept
: rule_(rule),
  node_(node)
{
}

boost::optional<MatchContext::match_group> MatchContext::match_next()
{
  if( !this->rule_ || !this->node_ )
    return {};

  match_group mg;
  auto rule = this->rule_;
  while( rule && this->node_ )
  {
    if( rule->is_optional() )
    {
      // Optional rules can be matched anywhere up to the next match of a
      // mandatory rule
      bool has_wrapped = false;
      auto stop_rule = this->find_mandatory_rule(rule->next(), nullptr);
      if( !stop_rule )
      {
        stop_rule = this->find_mandatory_rule(this->rule_, rule);
        // if there are no mandatory rules at all
        if( stop_rule == rule )
          stop_rule = nullptr;
        has_wrapped = true;
      }

      // If there are no mandatory rules, match until end
      if( !stop_rule )
      {
        this->match_to_node(mg, rule, stop_rule, nullptr);
        if( mg.size() )
        {
          return mg;
        }
        else
        {
          // If there wasn't matched anything now, there won't be later matches
          this->node_ = nullptr;
          return {};
        }
      }
      else
      {
        // Find the matching node of the next mandatory rule
        auto stop_node = this->find_match(this->node_, nullptr, stop_rule);

        // If the stop_rule is not included in this match_group
        if( has_wrapped )
        {
          // match until the last rule
          this->match_to_node(mg, rule, nullptr, stop_node);
          // If there was no match found for the mandatory rule, then don't
          // search for it in the next call to match_next()
          if( !stop_node )
            this->node_ = nullptr;
          return mg;
        }
        // If stop_rule wasn't found, abort (stop_rule is mandatory)
        else if( !stop_node )
        {
          this->node_ = nullptr;
          return {};
        }
        // If stop_rule is included in this match_group
        else
        {
          this->match_to_node(mg, rule, stop_rule, stop_node);
          // Also include the already matched stop_rule
          mg.push_back(std::make_pair(stop_rule, stop_node));
          rule = stop_rule->next();
          this->node_ = NextNode(stop_node);
        }
      }
    }
    else // rule is mandatory
    {
      this->node_ = this->find_match(this->node_, nullptr, rule);

      // If a mandatory rule isn't found, abort immediately
      if( !this->node_ )
        return {};

      mg.push_back(std::make_pair(rule, this->node_));
      this->node_ = NextNode(this->node_);
      rule = rule->next();
    }
  }

  // Optional rules can be skipped
  while( rule && rule->is_optional() )
    rule = rule->next();

  if( !rule )
    return mg;

  this->node_ = nullptr;
  return {};
}

const Rule *
MatchContext::find_mandatory_rule(const Rule * begin, const Rule * end) const
{
  while( begin && begin != end )
  {
    if( !begin->is_optional() )
      return begin;
    begin = begin->next();
  }

  return end;
}

const GumboNode * MatchContext::find_match(const GumboNode * begin,
                                           const GumboNode * end,
                                           const Rule *      rule) const
{
  assert(rule);
  while( begin && begin != end )
  {
    if( rule->matches(begin) )
      return begin;
    begin = NextNode(begin);
  }

  return end;
}

void MatchContext::match_to_node(match_group&      mg,
                                 const Rule *      rule,
                                 const Rule *      stop_rule,
                                 const GumboNode * stop_node)
{
  while( this->node_ && this->node_ != stop_node &&
         rule && rule != stop_rule )
  {
    auto matching_node = this->find_match(this->node_, stop_node, rule);
    if( matching_node && matching_node != stop_node )
    {
      mg.push_back(std::make_pair(rule, matching_node));
      this->node_ = NextNode(matching_node);
    }
    rule = rule->next();
  }
}


} // namespace hext


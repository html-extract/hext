#include "RuleMatching.h"

#include "hext/Rule.h"
#include "NodeUtil.h"


namespace hext {


const GumboNode * MatchRuleGroup(const Rule *      rule,
                                 const GumboNode * node,
                                 MatchingNodes&    result)
{
  if( !rule || !node )
    return nullptr;

  auto first_rule = rule;
  MatchingNodes sub;
  while( rule && node )
  {
    if( rule->is_optional() )
    {
      // Optional rules can be matched anywhere up to the next match of a
      // mandatory rule

      // Flag to tell whether the next mandatory rule falls into the current
      // result set or the next one.
      bool has_wrapped = false;

      // Get the next mandatory rule within (rule,rule-end)
      auto stop_rule = FindMandatoryRule(rule->next(), nullptr);
      if( !stop_rule )
      {
        // Get the next mandatory rule within [first_rule, rule)
        stop_rule = FindMandatoryRule(first_rule, rule);

        // if there are no mandatory rules at all
        if( stop_rule == rule )
          stop_rule = nullptr;

        has_wrapped = true;
      }

      // If there are no mandatory rules, match until end
      if( !stop_rule )
      {
        node = MatchRange(rule, nullptr, node, nullptr, sub);
        std::move(sub.begin(), sub.end(), std::back_inserter(result));
        return node ? NextNode(node) : nullptr;
      }
      // else match until the match of the next mandatory rule
      else
      {
        // If the stop_rule is not included in this match_group
        if( has_wrapped )
        {
          // Match the next node, but discard the result.
          // TODO: This is obviously wasteful.
          MatchingNodes discard;
          auto stop_node = MatchRuleOnce(stop_rule, node, nullptr, discard);

          // Match until the last rule: either there are only optional rules
          // following, or no rules.
          node = MatchRange(rule, nullptr, node, stop_node, sub);

          // If there was no match found for the mandatory rule, then matching
          // is done.
          if( !stop_node )
            node = nullptr;

          std::move(sub.begin(), sub.end(), std::back_inserter(result));
          return node ? NextNode(node) : nullptr;
        }
        else
        {
          // Match the next mandatory rule
          auto stop_node = MatchRuleOnce(stop_rule, node, nullptr, sub);

          if( !stop_node )
          {
            // Here, the stop rule is mandatory, and is part of the current
            // result set, but was not matched, so we can abort.
            return nullptr;
          }
          else
          {
            node = MatchRange(rule, stop_rule, node, stop_node, sub);
            // Also include the already matched stop_rule
            sub.push_back({stop_rule, stop_node});
            rule = stop_rule->next();
            node = NextNode(stop_node);
          }
        }
      }
    }
    else // rule is mandatory
    {
      node = MatchRuleOnce(rule, node, nullptr, sub);

      // If a mandatory rule isn't found, abort immediately
      if( !node )
        return nullptr;

      sub.push_back({rule, node});
      node = NextNode(node);
      rule = rule->next();
    }
  }

  // Optional rules can be skipped
  while( rule && rule->is_optional() )
    rule = rule->next();

  if( !rule )
  {
    // Here, all rules (at least all mandatory rules) were matched.
    std::move(sub.begin(), sub.end(), std::back_inserter(result));
    return node ? NextNode(node) : nullptr;
  }

  return nullptr;
}

bool RuleMatchesNodeRecursive(const Rule *      rule,
                              const GumboNode * node,
                              MatchingNodes&    result)
{
  if( !rule || !node )
    return false;

  if( !rule->matches(node) )
    return false;

  if( !rule->child() )
    return true;

  if( node->type != GUMBO_NODE_ELEMENT || !node->v.element.children.length )
    return false;

  auto first_child = static_cast<const GumboNode *>(
      node->v.element.children.data[0]);

  bool matched = false;
  auto next_node = first_child;

  do
  {
    MatchingNodes sub;
    next_node = MatchRuleGroup(rule->child(), next_node, sub);
    if( sub.size() )
    {
      std::move(sub.begin(), sub.end(), std::back_inserter(result));
      matched = true;
    }
  }
  while( next_node );

  return matched;
}

const GumboNode * MatchRuleOnce(const Rule *      rule,
                                const GumboNode * begin,
                                const GumboNode * end,
                                MatchingNodes&    result)
{
  assert(rule);
  if( !rule )
    return end;

  while( begin && begin != end )
  {
    if( RuleMatchesNodeRecursive(rule, begin, result) )
      return begin;
    begin = NextNode(begin);
  }

  return end;
}

const GumboNode * MatchRange(const Rule *      r_begin,
                             const Rule *      r_end,
                             const GumboNode * n_begin,
                             const GumboNode * n_end,
                             MatchingNodes&    result)
{
  while( n_begin && n_begin != n_end &&
         r_begin && r_begin != r_end )
  {
    auto matching_node = MatchRuleOnce(r_begin, n_begin, n_end, result);
    if( matching_node && matching_node != n_end )
    {
      result.push_back({r_begin, matching_node});
      n_begin = NextNode(matching_node);
    }
    r_begin = r_begin->next();
  }

  return n_begin;
}

const Rule * FindMandatoryRule(const Rule * begin, const Rule * end)
{
  while( begin && begin != end )
  {
    if( !begin->is_optional() )
      return begin;
    begin = begin->next();
  }

  return end;
}


} // namespace hext

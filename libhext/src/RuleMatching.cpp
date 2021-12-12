// Copyright 2015-2021 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "RuleMatching.h"

#include "hext/MaxSearchError.h"
#include "hext/Rule.h"
#include "NodeUtil.h"


namespace hext {


void SaveMatchingNodesRecursive(const Rule *                rule,
                                const GumboNode *           node,
                                std::vector<MatchingNodes>& result,
                                std::uint64_t&              max_searches)
{
  assert(node && rule);
  if( !node || !rule )
    return;

  if( max_searches && --max_searches == 0 )
    throw MaxSearchError("The allowed amount of searches was exhausted");

  const GumboNode * next_node = node;
  while( next_node )
  {
    MatchingNodes sub;
    next_node = MatchRuleGroup(rule, next_node, sub, max_searches);
    if( sub.size() )
      result.push_back(std::move(sub));
  }

  next_node = node;
  do
  {
    if( next_node->type == GUMBO_NODE_ELEMENT &&
        next_node->v.element.children.length )
    {
      auto next_node_first_child = static_cast<const GumboNode *>(
          next_node->v.element.children.data[0]);

      SaveMatchingNodesRecursive(
          rule, next_node_first_child, result, max_searches);
    }
  }
  while( (next_node = NextNode(next_node)) );
}

const GumboNode * MatchRuleGroup(const Rule *      rule,
                                 const GumboNode * node,
                                 MatchingNodes&    result,
                                 std::uint64_t&    max_searches)
{
  if( !rule || !node )
    return nullptr;

  MatchingNodes sub;
  auto first_rule = rule;
  while( rule && node )
  {
    auto rule_is_greedy_and_has_matched = rule->is_greedy() &&
                                          sub.size() &&
                                          rule == sub.back().first;
    if( rule->is_optional() || rule_is_greedy_and_has_matched )
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
        node = MatchRange(rule, nullptr, node, nullptr, sub, max_searches);
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
          auto stop_node = MatchRuleOnce(stop_rule, node, nullptr, discard, max_searches);

          // Match until the last rule: either there are only optional rules
          // following, or no rules, because the next mandatory rule is not
          // included in this result set.
          // Match until and excluding stop_node.
          node = MatchRange(rule, nullptr, node, stop_node, sub, max_searches);

          std::move(sub.begin(), sub.end(), std::back_inserter(result));
          return stop_node;
        }
        else
        {
          // Match the next mandatory rule
          auto stop_node = MatchRuleOnce(stop_rule, node, nullptr, sub, max_searches);

          if( !stop_node )
          {
            // Here, the stop rule is mandatory, and is part of the current
            // result set, but was not matched, so we can abort.
            return nullptr;
          }
          else
          {
            MatchRange(rule, stop_rule, node, stop_node, sub, max_searches);
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
      node = MatchRuleOnce(rule, node, nullptr, sub, max_searches);

      // If a mandatory rule isn't matched, abort immediately
      if( !node )
        return nullptr;

      sub.push_back({rule, node});
      if( !rule->is_greedy() )
        rule = rule->next();
      node = NextNode(node);
    }
  }

  // Rules that are greedy and were just matched can be skipped
  if( rule && rule->is_greedy() && sub.size() && rule == sub.back().first )
    rule = rule->next();

  // Optional rules can be skipped
  while( rule && rule->is_optional() )
    rule = rule->next();

  if( !rule )
  {
    // Here, all rules (at least all mandatory rules) were matched.
    std::move(sub.begin(), sub.end(), std::back_inserter(result));
    return node;
  }

  return nullptr;
}

bool RuleMatchesNodeRecursive(const Rule *      rule,
                              const GumboNode * node,
                              MatchingNodes&    result,
                              std::uint64_t&    max_searches)
{
  if( !rule || !node )
    return false;

  if( !rule->matches(node) )
    return false;

  if( !rule->child() && rule->nested().empty() )
    return true;

  if( node->type != GUMBO_NODE_ELEMENT || !node->v.element.children.length )
    return false;

  auto first_child = static_cast<const GumboNode *>(
      node->v.element.children.data[0]);

  MatchingNodes subresult;

  if( rule->child() )
  {
    bool matched = false;
    auto next_node = first_child;

    do
    {
      MatchingNodes sub;
      next_node = MatchRuleGroup(rule->child(), next_node, sub, max_searches);
      if( sub.size() )
      {
        std::move(sub.begin(), sub.end(), std::back_inserter(subresult));
        matched = true;
      }
      else if( !FindMandatoryRule(rule->child(), nullptr) )
      {
        matched = true;
      }
    }
    while( next_node );

    if( !matched )
      return false;
  }

  if( rule->nested().size() )
  {
    for( const auto& nested : rule->nested() )
    {
      std::vector<MatchingNodes> mn;
      SaveMatchingNodesRecursive(&nested, first_child, mn, max_searches);

      if( mn.empty() && FindMandatoryRule(&nested, nullptr) )
        return false;

      for(auto& e : mn)
        std::move(e.begin(), e.end(), std::back_inserter(subresult));
    }
  }

  std::move(subresult.begin(), subresult.end(), std::back_inserter(result));

  return true;
}

const GumboNode * MatchRuleOnce(const Rule *      rule,
                                const GumboNode * begin,
                                const GumboNode * end,
                                MatchingNodes&    result,
                                std::uint64_t&    max_searches)
{
  assert(rule);
  if( !rule )
    return end;

  while( begin && begin != end )
  {
    if( RuleMatchesNodeRecursive(rule, begin, result, max_searches) )
      return begin;
    begin = NextNode(begin);
  }

  return end;
}

const GumboNode * MatchRange(const Rule *      r_begin,
                             const Rule *      r_end,
                             const GumboNode * n_begin,
                             const GumboNode * n_end,
                             MatchingNodes&    result,
                             std::uint64_t&    max_searches)
{
  assert(n_begin);
  if( !n_begin )
    return n_end;

  const GumboNode * matching_node = n_end;
  while( r_begin && r_begin != r_end )
  {
    matching_node = MatchRuleOnce(r_begin, n_begin, n_end, result, max_searches);
    const auto has_matched = ( matching_node && matching_node != n_end );
    if( has_matched )
    {
      result.push_back({r_begin, matching_node});
      n_begin = NextNode(matching_node);
    }
    
    if( !(r_begin->is_greedy() && has_matched) )
      r_begin = r_begin->next();
  }

  return matching_node;
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


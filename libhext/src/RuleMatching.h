// Copyright 2015 Thomas Trapp
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

#ifndef HEXT_RULEMATCHING_H_INCLUDED
#define HEXT_RULEMATCHING_H_INCLUDED

#include "hext/Rule.h"

#include <utility>
#include <vector>

#include <gumbo.h>


namespace hext {


using MatchingNodes = std::vector<std::pair<const Rule *, const GumboNode *>>;


/// Calls MatchRuleGroup for each node in the given node tree and saves all
/// matching nodes in result. Result will only contain complete matches.
/// Result will be empty if nothing was matched.
void SaveMatchingNodesRecursive(const Rule *                rule,
                                const GumboNode *           node,
                                std::vector<MatchingNodes>& result);

/// Matches rule and its siblings against node and its siblings.
/// Saves the matching nodes in result, which will be empty, if no matches were
/// found.
/// Returns the node after the last matching node. Returns nullptr if matching
/// is done.
const GumboNode * MatchRuleGroup(const Rule *      rule,
                                 const GumboNode * node,
                                 MatchingNodes&    result);

/// Returns whether rule matches node. Also matches the rule's children against
/// the nodes children.
/// Saves the matching nodes that were found by recursion to result.
/// Note: Even if the given node matches, it won't be appended to result.
bool RuleMatchesNodeRecursive(const Rule *      rule,
                              const GumboNode * node,
                              MatchingNodes&    result);

/// Returns the first node in range [begin, end) for which
/// RuleMatchesNodeRecursive returns true.
/// Saves the matching nodes that were found by recursion to result.
/// Note: The returned matching node and given rule are not contained in the
/// result.
/// Returns end if no match is found. If no match is found, result will be
/// empty.
const GumboNode * MatchRuleOnce(const Rule *      rule,
                                const GumboNode * begin,
                                const GumboNode * end,
                                MatchingNodes&    result);

/// Matches rules in range [r_begin, r_end) against the nodes in range
/// [n_begin, n_end). Returns the last matching node, or n_end if all nodes
/// were matched. Rules are treated as if they are optional: If no match is
/// found for a rule, it is simply skipped.
/// Saves all matching nodes into result.
const GumboNode * MatchRange(const Rule *      r_begin,
                             const Rule *      r_end,
                             const GumboNode * n_begin,
                             const GumboNode * n_end,
                             MatchingNodes&    result);

/// Returns the next mandatory rule in range [begin, end), or nullptr, if no
/// mandatory rule is found.
const Rule * FindMandatoryRule(const Rule * begin, const Rule * end);


} // namespace hext


#endif // HEXT_RULEMATCHING_H_INCLUDED


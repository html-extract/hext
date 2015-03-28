#ifndef HEXT_RULE_H_INCLUDED
#define HEXT_RULE_H_INCLUDED

#include "hext/NodeUtil.h"
#include "hext/MakeUnique.h"
#include "hext/RulePatterns.h"

#include <string>
#include <vector>
#include <memory>

#include <gumbo.h>


namespace hext {


class ResultTree;

/// A Rule represents a source line from the hext input.
/// Generally: (<|>)is_optional?tag_name?:trait? rule_pattern*>?
///   Example: <div id="container" class="list">
///
/// A Rule matches an html-node if all its attributes are satisfied:
///  * is_optional: Ignored while matching. When ResultTree::filter is called,
///    invalid ResultTree branches are removed, unless this flag is set.
///  * any_descendant: Matching html-nodes may appear anywhere in the tree, as
///    opposed to direct descendants (default) which may only match if its
///    immediate parent node was matched.
///  * gumbo_tag: The tag_name of the rule, as parsed by gumbo. Matches if the
///    node's tag is the same. Set to GUMBO_TAG_UNKNOWN if any tag may match.
///  * trait: Traits describe the node that must match. For example:
///    :nth-child(2n), :last-child. Traits are stored as MatchPatterns.
///  * RulePatterns: If the rule is closed,
///    RulePatterns::matches_all_attributes() must return true. If the Rule is
///    not optional, RulePatterns::matches() must return true.
///  * is_closed: A Rule is closed, if it ends with '>'.
///
/// If a node matches a Rule, RulePatterns::capture() is called, which returns
/// a new ResultTree branch, containing all captured NameValuePairs.
///
/// A Rule is a tree: each Rule has a vector of child-rules.
class Rule
{
public:
  Rule(
    GumboTag gumbo_tag,
    bool is_optional,
    bool is_any_descendant,
    bool closed,
    RulePatterns&& r_patterns
  );
  Rule(Rule&&) = default;
  Rule(const Rule&) = default;
  Rule& operator=(Rule&&) = default;
  Rule& operator=(const Rule&) = default;

  /// Append child-rule after last element at tree-level level.
  /// Example Rule:
  ///   level0  <div>       # this
  ///   level1    <li>
  ///   level2      <span>
  ///   level1    <li>
  ///   level2      <img>
  ///
  /// this->append_child(<a>, 2):
  ///   level0  <div>      # this
  ///   level1    <li>
  ///   level2      <span>
  ///   level1    <li>
  ///   level2      <img>
  ///   level2      <a>    # new
  ///
  /// Only used when constructing Rules in the parser.
  void append_child(Rule&& r, int level = 1);

  /// Expose child rules. ResultTree::filter needs to know about the complete
  /// rule tree to decide if all rules were matched.
  const std::vector<Rule>& children() const;

  /// Returns true if this rule is optional. A rule is optional, if it does not
  /// participate in validation.
  bool optional() const;

  /// Recursively try to find and capture matches.
  void extract(const GumboNode * node, ResultTree * r) const;

private:
  /// Check wheter this Rule matches a single GumboNode.
  bool matches(const GumboNode * node) const;

  /// Helper method that calls Rule::extract for each child of GumboNode.
  void extract_node_children(const GumboNode * node, ResultTree * rt) const;

  /// The children of this rule.
  std::vector<Rule> children_;

  /// RulePatterns contain both MatchPatterns and CapturePatterns. RulePatterns
  /// were introduced to lessen the amount of code in Rule.
  RulePatterns patterns_;

  /// The type of html-tag this rule matches, as parsed by gumbo. Set to
  /// GUMBO_TAG_UNKNOWN if this rule has no tag. Html-tags that aren't defined
  /// by the html spec have at this stage already been rejected by the parser.
  const GumboTag gumbo_tag_;

  /// A rule is optional if it does not participate in validation.
  const bool is_optional_;

  /// If true, matching html-nodes may appear anywhere in the html.
  /// If false, Rule matches only if its immediate parent was matched.
  const bool is_any_descendant_;

  /// If a rule is closed, html-nodes matching this rule must have all
  /// attributes specified in the rule definition, but no more.
  const bool is_closed_;
}; 


} // namespace hext


#endif // HEXT_RULE_H_INCLUDED


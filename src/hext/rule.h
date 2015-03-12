#ifndef HEXT_RULE_H_INCLUDED
#define HEXT_RULE_H_INCLUDED

#include "hext/node-util.h"
#include "hext/make-unique.h"
#include "hext/rule-patterns.h"

#include <string>
#include <vector>
#include <memory>

#include <gumbo.h>


namespace hext {


class ResultTree;

/// A Rule represents a source line from the hext input.
/// Generally: <is_optional?(dd|nth_child)?tag_name? rule_pattern*>
///   Example: <!2div id="container" class="list">
///
/// A Rule matches an html-node if all its attributes are satisfied:
///  * is_optional: Ignored while matching. When ResultTree::filter is called,
///    invalid ResultTree branches are removed, unless this flag is set.
///  * nth_child or direct_descendant: Matches if the node is a direct
///    descendant of its parent. If nth_child is given, it must match the index
///    within its parent node (the index is determined by ignoring text-nodes,
///    see node-util's GetNodePositionWithinParent)
///  * gumbo_tag: The tag_name of the rule, as parsed by gumbo. Matches if the
///    node's tag is the same. Set to GUMBO_TAG_UNKNOWN if any tag may match.
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
    int nth_child,
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

  /// The type of html-tag this rule matches, as parsed by gumbo. Returns
  /// GUMBO_TAG_UNKNOWN this rule has no tag. Html-tags that aren't defined by
  /// the html spec have at this stage already been rejected by the parser.
  GumboTag gumbo_tag() const;

  /// Returns true if this rule is optional. A rule is optional, if it does not
  /// participate in validation.
  bool optional() const;

  /// Recursively try to find and capture matches.
  void extract(const GumboNode * node, ResultTree * r) const;

  /// Recursively print the Rule and its child-rules.
  void print(
    std::ostream& out = std::cout,
    int indent_level = 0
  ) const;

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

  /// If nth_child_ is greater than zero, html-nodes matching this rule must
  /// match the index within its parent node (the index is determined by
  /// ignoring text-nodes, see node-util's GetNodePositionWithinParent).
  /// Else, if nth_child_ is less than one, html-nodes matching this rule must
  /// be a direct descendant of their parents.
  const int nth_child_;

  /// If a rule is closed, html-nodes matching this rule must have all
  /// attributes specified in the rule definition, but no more.
  const bool is_closed_;
}; 


} // namespace hext


#endif // HEXT_RULE_H_INCLUDED


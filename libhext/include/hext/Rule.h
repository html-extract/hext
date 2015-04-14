#ifndef HEXT_RULE_H_INCLUDED
#define HEXT_RULE_H_INCLUDED

#include "hext/Result.h"
#include "hext/NodeUtil.h"
#include "hext/MakeUnique.h"
#include "hext/pattern/MatchPattern.h"
#include "hext/pattern/CapturePattern.h"

#include <string>
#include <vector>
#include <memory>

#include <gumbo.h>


namespace hext {


class ResultTree;

/// A Rule defines how to match and capture html-nodes. It can be applied to a
/// GumboNode tree, where it recursively tries to find matches. Once a match is
/// found, the Rule appends a new branch to a ResultTree (which is supplied by
/// the caller), containing the captured values of an html-node.
///
/// A Rule is also a tree. A Rule can have multiple Rule children.
///
/// Matching is done in a recursive and brute-force manner: A Rule is matched
/// against every child of the given GumboNode tree. Additionally, if a Rule
/// matches a subnode of the html-tree, all its Rule children are matched
/// against this subtree.
///
/// A Rule may produce incomplete ResultTrees. An incomplete ResultTree occurs
/// if a Rule matches, but its children or siblings do not. This omission
/// greatly simplifies recursive matching.
/// `ResultTree::remove_incomplete_branches()` is provided to remove incomplete
/// ResultTree branches.
class Rule
{
public:
  /// Construct a Rule.
  ///
  /// \param gumbo_tag
  ///    The tag_name of the rule, as parsed by gumbo. Matches if the node's tag
  ///    is the same. Set to GUMBO_TAG_UNKNOWN if any tag may match.
  ///
  /// \param is_optional
  ///    When `ResultTree::remove_incomplete_branches()` is called, invalid
  ///    ResultTree branches are removed, unless the Rule that produced the
  ///    branch is optional.
  ///
  /// \param is_any_descendant
  ///    Matching html-nodes may appear anywhere in the current subtree, as
  ///    opposed to direct descendants (default) which may only match if its
  ///    immediate parent node was matched.
  ///
  /// \param is_path
  ///    Rules that are paths do not capture values, they only describe a path
  ///    to an html-node from which to start extracting.
  ///
  /// \param match_patterns
  ///    A vector of MatchPatterns. MatchPatterns check whether an html-node
  ///    matches. MatchPatterns are wrapped in a std::unique_ptr to allow for
  ///    polymorphism.
  ///
  /// \param capture_patterns
  ///    A vector of CapturePatterns. CapturePatterns extract name-value pairs
  ///    from html-nodes. Like `match_patterns`, the CapturePatterns are wrapped
  ///    in a std::unique_ptr to allow for polymorphism.
  Rule(
    GumboTag gumbo_tag,
    bool is_optional,
    bool is_any_descendant,
    bool is_path,
    std::vector<std::unique_ptr<MatchPattern>>&& match_patterns,
    std::vector<std::unique_ptr<CapturePattern>>&& capture_patterns
  );
  Rule(Rule&&) = default;
  Rule& operator=(Rule&&) = default;

  /// Append child-rule after last element at tree-level level.
  /// Example Rule:
  /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
  /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ///
  /// Only used when constructing Rules in the parser.
  void append_child(Rule&& r, int level = 1);

  /// Expose child rules. `ResultTree::remove_incomplete_branches()` needs to
  /// know about the complete rule tree to decide if all rules were matched.
  const std::vector<Rule>& children() const;

  /// Returns true if this rule is optional. A rule is optional, if it does not
  /// participate in validation.
  bool optional() const;

  /// Recursively try to find and capture matches.
  void extract(const GumboNode * node, ResultTree * r) const;

private:
  /// Check wheter this Rule matches a single GumboNode.
  bool matches(const GumboNode * node) const;

  /// Return the result of applying all CapturePatterns to node.
  std::vector<ResultPair> capture(const GumboNode * node) const;

  /// Helper method that calls Rule::extract for each child of GumboNode.
  void extract_node_children(const GumboNode * node, ResultTree * rt) const;

  /// The children of this rule.
  std::vector<Rule> children_;

  /// The MatchPatterns of this rule.
  std::vector<std::unique_ptr<MatchPattern>> match_patterns_;

  /// The CapturePatterns of this rule.
  std::vector<std::unique_ptr<CapturePattern>> capture_patterns_;

  /// The type of html-tag this rule matches, as parsed by gumbo. Set to
  /// GUMBO_TAG_UNKNOWN if this rule should match any tag. Html-tags that
  /// aren't defined by the html spec have at this stage already been rejected
  /// by the parser.
  const GumboTag gumbo_tag_;

  /// A rule is optional if it does not participate in validation.
  const bool is_optional_;

  /// If true, matching html-nodes may appear anywhere in the html.
  /// If false, Rule matches only if its immediate parent was matched.
  const bool is_any_descendant_;

  /// If true, do not capture values.
  const bool is_path_;
}; 


} // namespace hext


#endif // HEXT_RULE_H_INCLUDED


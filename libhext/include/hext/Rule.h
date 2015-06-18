#ifndef HEXT_RULE_H_INCLUDED
#define HEXT_RULE_H_INCLUDED

#include "hext/Result.h"
#include "hext/ResultTree.h"
#include "hext/NodeUtil.h"
#include "hext/MakeUnique.h"
#include "hext/MatchContext.h"
#include "hext/pattern/MatchPattern.h"
#include "hext/pattern/CapturePattern.h"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include <gumbo.h>


namespace hext {


/// A Rule defines how to match and capture html-nodes. It can be applied to a
/// GumboNode tree, where it recursively tries to find matches. Once a match is
/// found, the Rule appends a new branch to a ResultTree (which is supplied by
/// the caller), containing the captured values of an html-node.
///
/// A Rule is also a tree: A Rule can have multiple Rule children.
///
/// Matching is done in a recursive and brute-force manner: A Rule is matched
/// against every child of the given GumboNode tree. Additionally, if a Rule
/// matches a subnode of the html-tree, all its Rule children are matched
/// against this subtree.
class Rule
{
public:
  /// Construct a Rule.
  ///
  /// \param tag
  ///    The tag-name of the rule, as parsed by gumbo. Matches if the node's tag
  ///    is the same. Set to GUMBO_TAG_UNKNOWN if any tag may match.
  ///
  /// \param is_optional
  ///    A subtree matches only if all mandatory rules were matched. Optional
  ///    rules on the other hand are ignored if not found.
  ///
  /// \param is_any_descendant
  ///    Matching html-nodes may appear anywhere in the current subtree, as
  ///    opposed to direct descendants (default) which may only match if its
  ///    immediate parent node was matched.
  explicit Rule(
    GumboTag tag = GUMBO_TAG_UNKNOWN,
    bool optional = false,
    bool any_descendant = false
  );

  /// Append a child-rule after the last element at the given tree depth.
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
  void append_child(Rule&& r, std::size_t tree_depth);

  /// Emplace a MatchPattern.
  template<typename MatchPatternType, typename... Args>
  void add_match_pattern(Args&&... arg)
  {
    this->match_patterns_.push_back(
      MakeUnique<MatchPatternType>(std::forward<Args>(arg)...)
    );
  }

  /// Emplace a CapturePattern.
  template<typename CapturePatternType, typename... Args>
  void add_capture_pattern(Args&&... arg)
  {
    this->capture_patterns_.push_back(
      MakeUnique<CapturePatternType>(std::forward<Args>(arg)...)
    );
  }

  /// Return the type of html-tag this rule matches, as parsed by gumbo.
  /// Return GUMBO_TAG_UNKNOWN if this rule matches any tag.
  GumboTag get_tag() const { return this->tag_; }

  /// Set the type of html-tag this rule matches, as parsed by gumbo. Set to
  /// GUMBO_TAG_UNKNOWN if this rule should match any tag.
  void set_tag(GumboTag tag) { this->tag_ = tag; }

  /// Return true if this rule is optional, i.e. if a match has to be found.
  bool is_optional() const { return this->is_optional_; }

  /// Set whether this rule is optional, i.e. if a match has to be found.
  void set_optional(bool optional) { this->is_optional_ = optional; }

  /// Return true if matching html-nodes may appear anywhere in the html.
  /// If false, this Rule matches only if its immediate parent was matched.
  bool is_any_descendant() const { return this->is_any_descendant_; }

  /// Set whether matching html-nodes may appear anywhere in the html.
  /// If false, this Rule matches only if its immediate parent was matched.
  void set_any_descendant(bool any_descendant)
    { this->is_any_descendant_ = any_descendant; }

  /// Recursively try to find and capture matches.
  std::unique_ptr<ResultTree> extract(const GumboNode * node) const;

  /// Check if this Rule matches a single GumboNode.
  bool matches(const GumboNode * node) const;

  /// Return the result of applying all CapturePatterns to node.
  std::vector<ResultPair> capture(const GumboNode * node) const;

private:
  /// Apply this rule to `node`, store results in `rt`
  bool extract_children(const GumboNode * node, ResultTree * rt) const;

  /// The children of this rule.
  std::vector<Rule> children_;

  /// A vector of MatchPatterns. MatchPatterns check whether an html-node
  /// matches. MatchPatterns are wrapped in a std::unique_ptr to allow for
  /// polymorphism.
  std::vector<std::unique_ptr<MatchPattern>> match_patterns_;

  /// A vector of CapturePatterns. CapturePatterns extract name-value pairs
  /// from html-nodes. Like `match_patterns`, the CapturePatterns are wrapped
  /// in a std::unique_ptr to allow for polymorphism.
  std::vector<std::unique_ptr<CapturePattern>> capture_patterns_;

  /// The type of html-tag this rule matches, as parsed by gumbo. Set to
  /// GUMBO_TAG_UNKNOWN if this rule should match any tag. Html-tags that
  /// aren't defined by the html spec have at this stage already been rejected
  /// by the parser.
  GumboTag tag_;

  /// A rule is optional if it does not participate in validation.
  bool is_optional_;

  /// If true, matching html-nodes may appear anywhere in the html.
  /// If false, Rule matches only if its immediate parent was matched.
  bool is_any_descendant_;
}; 


} // namespace hext


#endif // HEXT_RULE_H_INCLUDED


#ifndef HEXT_RULE_H
#define HEXT_RULE_H

#include <string>
#include <vector>
#include <memory>

#include <gumbo.h>

#include "hext/make-unique.h"
#include "hext/attribute.h"


namespace hext {


class match_tree;

/// A rule represents a source line from the hext input.
/// Generally: <tag_name? attribute*>
///   Example: <div id="container">
///
/// tag_name represents the html-tag that we want to match. Empty tag_name
/// matches any html-tag.
/// A rule's attributes can be matched against an html-tag and capture values
/// to be used in the result (match_tree).
/// A rule is a tree: each rule has a vector of child-rules.
class rule
{
public:
  rule();

  /// Append child-rule after last element at tree-level level.
  /// Example rule:
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
  void append_child(const rule& r, int level = 0);
  void append_attribute(attribute attr);

  std::vector<rule>::size_type children_size() const;
  std::string get_tag_name() const;
  void set_tag_name(std::string name);

  /// Recursively try to find and capture matches.
  /// Call this->matches(node):
  /// * if true, capture contents and append them to the match_tree.
  ///   Then call each child-rule's rule::match, for each child of node
  /// * if false, call this->match for each child of node.
  void match(const GumboNode * node, match_tree * m) const;

  /// Capture attributes from a single GumboNode.
  /// Returns a single match_tree.
  std::unique_ptr<match_tree> capture(const GumboNode * node) const;

  /// Recursively print the rule and its child-rules, including attributes
  /// and tag-name.
  void print(std::ostream& out = std::cout, int indent_level = 0) const;

private:
  /// Check wheter this rule matches a single GumboNode.
  /// A rule matches when each attribute is found in the GumboNode and
  /// tag-name is equal (if non empty).
  bool matches(const GumboNode * node) const;

  /// Helper method that calls rule::match for each child of GumboNode.
  void match_node_children(const GumboNode * node, match_tree * m) const;

  std::vector<rule> children;
  std::vector<attribute> attributes;

  std::string tag_name;
};  


} // namespace hext


#endif // HEXT_RULE_H


#ifndef HEXT_MATCH_TREE_H
#define HEXT_MATCH_TREE_H

#include <cassert>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


namespace hext {


class rule;

/// A match_tree contains the result of matching a rule to GumboNodes through
/// rule::match().
class match_tree
{
public:
  typedef
    std::pair<std::string, std::string>
    name_value_pair;

  match_tree();

  match_tree * append_child_and_own(std::unique_ptr<match_tree> m);
  void append_match(const name_value_pair& p);
  void set_rule(const rule * matching_rule);

  /// Print the match_tree as json.
  /// Each child of the root of the match_tree will form its own json object.
  void print_json(std::ostream& out = std::cout) const;

  /// Print the match_tree as DOT, a graph description language.
  /// See http://en.wikipedia.org/wiki/DOT_language
  void print_dot(std::ostream& out = std::cout) const;

  /// Remove all nodes that do not conform to the rule tree,
  /// leaving a clean match_tree with only valid results.
  /// When recursively matching GumboNodes in rule::match we do not want to
  /// care about wether a match will eventually be valid. Dropping invalid
  /// matches is much easier after we have processed all input.
  /// Returns true on empty match_tree.
  bool filter();

private:
  match_tree(const match_tree&) = delete;
  match_tree& operator=(const match_tree&) = delete;

  void append_json_recursive(rapidjson::Document& json) const;
  void append_json_matches(rapidjson::Document& json) const;
  void print_dot_nodes(std::ostream& out, int parent_id = 0) const;

  /// match_trees are self-managing: all nodes are owned by the tree
  std::vector<std::unique_ptr<match_tree>> children;

  /// The values captured by matching
  std::vector<name_value_pair> matches;

  /// The rule that caused this match
  const rule * r;
};


} // namespace hext


#endif // HEXT_MATCH_TREE_H


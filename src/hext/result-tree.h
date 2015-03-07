#ifndef HEXT_RESULT_TREE_H_INCLUDED
#define HEXT_RESULT_TREE_H_INCLUDED

#include <cassert>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <map>

#include <rapidjson/document.h>


namespace hext {


/// Forward declare Rule because it depends on ResultTree.
class Rule;

/// A ResultTree contains the result of matching a Rule to GumboNodes through
/// Rule::extract().
class ResultTree
{
public:
  /// Convenience typedef for name-value-pairs. First member is the name of a
  /// capture, the second member is the value of a capture.
  typedef
    std::pair<std::string, std::string>
    NameValuePair;

  ResultTree();

  /// Append and own branch. Return a pointer to the new branch.
  ResultTree * append_child_and_own(std::unique_ptr<ResultTree> m);

  /// Append a NameValuePair to this branch.
  void append_result(const NameValuePair& p);

  /// Set the Rule that caused this ResultTree branch.
  void set_rule(const Rule * matching_rule);

  /// Return each ResultTree branch as a json object.
  /// Each child of the root of the ResultTree will form its own json object.
  std::vector<rapidjson::Document> to_json() const;

  /// Print the ResultTree as DOT, a graph description language.
  /// See http://en.wikipedia.org/wiki/DOT_language
  void print_dot(std::ostream& out = std::cout) const;

  /// Remove all nodes that do not conform to the rule tree,
  /// leaving a clean ResultTree with only valid results.
  /// When recursively matching GumboNodes in Rule::extract we do not want to
  /// care about wether a match will eventually be valid. Dropping invalid
  /// matches is much easier after we have processed all input.
  /// Do not remove optional Rules.
  /// Return true on empty ResultTree.
  bool filter();

  /// Convert every branch's values_ to a multimap and put them in a vector.
  std::vector<std::multimap<std::string, std::string>> to_vector() const;

private:
  ResultTree(const ResultTree&) = delete;
  ResultTree& operator=(const ResultTree&) = delete;

  /// Recursively insert all values_ into map.
  void save(std::multimap<std::string, std::string>& map) const;

  /// Recursively append all branches to the json document.
  void append_json_recursive(rapidjson::Document& json) const;

  /// Append a ResultTree's branch NameValuePairs to the json document.
  /// If a name already exists it is converted to an array and the new value is
  /// appended.
  ///
  /// For example, consider the key "foo" already being taken:
  ///   {"foo": "bar"}
  ///   then append_json_values is called, with a branch
  ///   containing NameValuePair("foo", "baz")
  /// Produces:
  ///   {"foo": ["bar", "baz"]}
  void append_json_values(rapidjson::Document& json) const;

  /// Recursivley print all DOT nodes. Each node has a distinct id. The
  /// parameter parent_id is neccessary to allow kids to connect to their
  /// parents.
  void print_dot_nodes(std::ostream& out, int parent_id = 0) const;

  /// ResultTrees are self-managing: all nodes are owned by the tree.
  std::vector<std::unique_ptr<ResultTree>> children_;

  /// The values captured by extracting.
  std::vector<NameValuePair> values_;

  /// The Rule that produced this instance's values_.
  const Rule * r_;
};


} // namespace hext


#endif // HEXT_RESULT_TREE_H_INCLUDED


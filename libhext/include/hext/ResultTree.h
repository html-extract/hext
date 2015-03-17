#ifndef HEXT_RESULT_TREE_H_INCLUDED
#define HEXT_RESULT_TREE_H_INCLUDED

#include "hext/Result.h"

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>


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

  explicit ResultTree(const Rule * rule);
  ResultTree(const Rule * rule, std::vector<NameValuePair> values);
  ResultTree(ResultTree&&) = default;

  /// Create a new branch. Return a pointer to the new branch.
  ResultTree * create_branch(
    const Rule * rule,
    std::vector<NameValuePair> values
  );

  /// Remove all nodes that do not conform to the rule tree,
  /// leaving a clean ResultTree with only valid results.
  /// When recursively matching GumboNodes in Rule::extract we do not want to
  /// care about wether a match will eventually be valid. Dropping invalid
  /// matches is much easier after we have processed all input.
  /// Do not remove optional Rules.
  /// Return true on empty ResultTree.
  bool filter();

  /// Convert every branch's values_ to a multimap and put them in a vector.
  Result to_result() const;

private:
  ResultTree(const ResultTree&) = delete;
  ResultTree& operator=(const ResultTree&) = delete;

  /// Recursively insert all values_ into map.
  void save(ResultMap& map) const;

  /// ResultTrees are self-managing: all nodes are owned by the tree.
  std::vector<std::unique_ptr<ResultTree>> children_;

  /// The values captured by extracting.
  const std::vector<NameValuePair> values_;

  /// The Rule that produced this instance's values_.
  const Rule * matching_rule_;
};


} // namespace hext


#endif // HEXT_RESULT_TREE_H_INCLUDED


#ifndef HEXT_RESULT_TREE_H_INCLUDED
#define HEXT_RESULT_TREE_H_INCLUDED

#include "hext/Result.h"

#include <vector>
#include <memory>


namespace hext {


/// A ResultTree contains the result of matching a Rule to GumboNodes through
/// `Rule::extract()`.
class ResultTree
{
public:
  ResultTree();
  ResultTree(ResultTree&&);
  ResultTree& operator=(ResultTree&&);
  ~ResultTree();

  /// Return a non-owning pointer to the newly created child.
  ResultTree * create_child();

  /// Delete a child branch pointed to by `child`. If `child` is not found
  /// nothing is done.
  void delete_child(const ResultTree * child);

  void set_values(std::vector<ResultPair> v);

  /// Return read-only access to values.
  const std::vector<ResultPair>& values() const;

  /// Return read-only access to children.
  const std::vector<std::unique_ptr<ResultTree>>& children() const;

  /// Return a vector containing multimaps of string pairs. Each element in the
  /// vector represents a child of this ResultTree. The multimaps are the result
  /// of recursively appending each subtree, flattening all values to a single
  /// map.
  /// Note: Values from this instance are omitted.
  Result flatten() const;

private:
  ResultTree(const ResultTree&) = delete;
  ResultTree& operator=(const ResultTree&) = delete;

  struct Impl;
  std::unique_ptr<Impl> impl_;
};


} // namespace hext


#endif // HEXT_RESULT_TREE_H_INCLUDED


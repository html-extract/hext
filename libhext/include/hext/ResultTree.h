#ifndef HEXT_RESULT_TREE_H_INCLUDED
#define HEXT_RESULT_TREE_H_INCLUDED

/// @file
///   Declares hext::ResultTree

#include "hext/Result.h"

#include <vector>
#include <memory>


namespace hext {


/// A self-managing tree containing all values captured from HTML.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   Rule rule = ParseHext(
///     "<a href={href}><img/></a>" // i.e. capture the attribute href from all
///                                 // anchor elements that have a child with
///                                 // HtmlTag <img>.
///   );
///   std::unique_ptr<ResultTree> rt = rule.extract([html]);
///   Result result = rt->flatten();
///   // Each element of result is an unordered multimap, each containing one
///   // string pair.
/// ~~~~~~~~~~~~~
class ResultTree
{
public:
  /// Constructs an empty ResultTree.
  ResultTree();

  ~ResultTree() noexcept;
  ResultTree(ResultTree&&) noexcept;
  ResultTree& operator=(ResultTree&&) noexcept;

  /// Appends a new branch.
  ///
  /// @returns  A non-owning pointer to the newly created child.
  ResultTree * create_child();

  /// Deletes the child branch pointed to by child.
  ///
  /// @param child:  The child branch wich will be deleted. If it is not a child
  ///                of this instance, the call will have no effect.
  void delete_child(const ResultTree * child);

  /// Sets the captured values for this branch.
  ///
  /// @param v:  A vector containing string-pairs.
  void set_values(std::vector<ResultPair> v) noexcept;

  /// Returns read-only access to the values of this tree node.
  const std::vector<ResultPair>& values() const noexcept;

  /// Returns read-only access to the children of this tree node.
  const std::vector<std::unique_ptr<ResultTree>>& children() const noexcept;

  /// Returns a vector<ResultMap> containing all values from all children.
  /// Each element of the vector represents a complete extraction done
  /// by a Rule.
  Result flatten() const;

private:
  ResultTree(const ResultTree&) = delete;
  ResultTree& operator=(const ResultTree&) = delete;

  /// Recursively inserts all values into map, including this instance's values.
  void save(ResultMap& map) const;

  std::vector<std::unique_ptr<ResultTree>> children_;
  std::vector<ResultPair> values_;
};


} // namespace hext


#endif // HEXT_RESULT_TREE_H_INCLUDED


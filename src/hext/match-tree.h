#ifndef HEXT_MATCH_TREE_H
#define HEXT_MATCH_TREE_H

#include <string>
#include <utility>
#include <vector>
#include <memory>


namespace hext {


class match_tree
{
public:
  typedef
    std::vector<std::unique_ptr<match_tree>>::const_iterator
    const_child_iterator;
  typedef
    std::pair<std::string, std::string>
    name_value_pair;
  typedef
    std::vector<std::pair<std::string, std::string>>::const_iterator
    const_match_iterator;

  match_tree();

  match_tree * append_child_and_own(std::unique_ptr<match_tree> m);

  void append_match(const name_value_pair& p);

  const_child_iterator children_begin() const;

  const_child_iterator children_end() const;

  std::vector<match_tree>::size_type children_size() const;

  const_match_iterator matches_begin() const;

  const_match_iterator matches_end() const;

private:
  match_tree(const match_tree&) = delete;
  match_tree& operator=(const match_tree&) = delete;

  std::vector<std::unique_ptr<match_tree>> children;
  std::vector<name_value_pair> matches;
};


} // namespace hext


#endif // HEXT_MATCH_TREE_H


#ifndef HEXT_MATCH_TREE_H
#define HEXT_MATCH_TREE_H

#include <cassert>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <iostream>

#include "hext/util.h"


namespace hext {


class match_tree
{
public:
  typedef
    std::pair<std::string, std::string>
    name_value_pair;

  match_tree();

  match_tree * append_child_and_own(std::unique_ptr<match_tree> m);

  void append_match(const name_value_pair& p);

  void to_json(std::ostream& out = std::cout) const;

  void print(std::ostream& out = std::cout, int indent_level = 0) const;

private:
  match_tree(const match_tree&) = delete;
  match_tree& operator=(const match_tree&) = delete;

  std::vector<std::unique_ptr<match_tree>> children;
  std::vector<name_value_pair> matches;
};


} // namespace hext


#endif // HEXT_MATCH_TREE_H


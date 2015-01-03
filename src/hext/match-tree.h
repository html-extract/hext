#ifndef HEXT_MATCH_TREE_H
#define HEXT_MATCH_TREE_H

#include <cassert>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

#include "hext/util.h"
#include "hext/infix-ostream-iterator.h"


namespace hext {


class rule;

class match_tree
{
public:
  typedef
    std::pair<std::string, std::string>
    name_value_pair;

  match_tree();

  match_tree * append_child_and_own(std::unique_ptr<match_tree> m);

  void append_match(const name_value_pair& p);

  void json_print(std::ostream& out = std::cout) const;
  void json_print_recursive(infix_ostream_iterator<std::string>& out) const;

  void print(std::ostream& out = std::cout) const;
  void print_dot(std::ostream& out, int parent_id = 0) const;

  void set_rule(const rule * matching_rule);

  void filter();
  bool filter_recursive();

private:
  match_tree(const match_tree&) = delete;
  match_tree& operator=(const match_tree&) = delete;

  std::vector<std::unique_ptr<match_tree>> children;
  std::vector<name_value_pair> matches;

  const rule * r;
};


} // namespace hext


#endif // HEXT_MATCH_TREE_H


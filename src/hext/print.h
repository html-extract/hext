#ifndef HEXT_PRINT_H
#define HEXT_PRINT_H

#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>

#include "hext/rule.h"
#include "hext/attribute.h"
#include "hext/match-tree.h"


namespace hext {


void print_match_tree(
  const match_tree * m,
  unsigned int indent_level = 0,
  std::ostream& out = std::cout
);


} // namespace hext


#endif // HEXT_PRINT_H


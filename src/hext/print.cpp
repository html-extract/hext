#include "hext/print.h"


namespace hext {


void print_match_tree(
  const match_tree * m,
  unsigned int indent_level,
  std::ostream& out
)
{
  assert(m != nullptr);
  out << ( indent_level ? std::string(indent_level * 2, ' ') : "" )
      << "match_tree matches: ";
  std::for_each(
    m->matches_begin(),
    m->matches_end(),
    [&out](const match_tree::name_value_pair& match) {
      out << match.first << ": " << match.second << "; ";
    }
  );
  out << "\n"
      << ( indent_level ? std::string(indent_level * 2, ' ') : "" )
      << "children("
      << std::distance(m->children_begin(), m->children_end())
      << "):\n";
  std::for_each(
    m->children_begin(),
    m->children_end(),
    [indent_level, &out](const std::unique_ptr<match_tree>& c) {
      print_match_tree(c.get(), indent_level + 1, out);
    }
  );
}


} // namespace hext


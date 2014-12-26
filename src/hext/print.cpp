#include "hext/print.h"


namespace hext {


void print_rule(
  rule r,
  unsigned int indent_level,
  std::ostream& out
)
{
  out << ( indent_level ? std::string(indent_level * 2, ' ') : "" )
      << "<"
      << r.get_tag_name()
      << " ";

  std::for_each(
    r.attributes_begin(),
    r.attributes_end(),
    [&out](attribute a) {
      out << a.get_name()
          << "=\""
          << ( a.is_capture() ? "(:" : "" )
          << a.get_value()
          << ( a.is_capture() ? ")" : "" )
          << "\" ";
    }
  );

  out << ">\n";
  std::for_each(
    r.children_begin(),
    r.children_end(),
    [indent_level, &out](rule c) {
      print_rule(c, indent_level + 1, out);
    }
  );
}

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


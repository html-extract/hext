#include "hext/match-tree.h"


namespace hext {


match_tree::match_tree()
: children(),
  matches(),
  complete(false)
{
}

match_tree * match_tree::append_child_and_own(std::unique_ptr<match_tree> m)
{
  this->children.push_back(std::move(m));
  return this->children.back().get();
}

void match_tree::append_match(const name_value_pair& p)
{
  this->matches.push_back(p);
}

void match_tree::json_print(std::ostream& out) const
{
  out << "{";
  infix_ostream_iterator<std::string> it_out(out, ", ");
  for(const auto& c : this->children)
  {
    c->json_print_recursive(it_out);
  }
  out << "}\n";
}

bool match_tree::json_print_recursive(infix_ostream_iterator<std::string>& out) const
{
  if( this->children.empty() )
  {
    if( this->complete )
      this->json_print_matches(out);

    return this->complete;
  }
  else
  {
    bool ret = false;
    for(const auto& c : this->children)
      ret |= c->json_print_recursive(out);

    if( ret )
      this->json_print_matches(out);

    return ret;
  }
}

void match_tree::json_print_matches(infix_ostream_iterator<std::string>& out) const
{
  for(auto it = this->matches.begin(); it != this->matches.end(); ++it)
  {
    std::string str("\"");
    str.append(util::escape_quotes(it->first))
       .append("\": \"")
       .append(util::escape_quotes(it->second))
       .append("\"");
    out = str;
  }
}

void match_tree::print(std::ostream& out) const
{
  out << "digraph match_tree {\n"
      << "    node [fontname=\"Arial\"];\n";
  this->print_dot(out);
  out << "}\n";
}

void match_tree::print_dot(std::ostream& out, int parent_id) const
{
  static int node_index = 0;
  int this_node = ++node_index;

  std::string label;
  if( this->matches.empty() )
    label.append("[rule]");
  else
    for(const auto& m : this->matches)
    {
      label.append(m.first);
      label.append(" ");
    }

  if( this->complete )
    label.append("*");

  out << "    node_" << this_node << " [label=\"" << label << "\"];\n";
  if( parent_id )
    out << "    node_" << parent_id << " -> node_" << this_node << ";\n";

  for(const auto& c : this->children)
    c->print_dot(out, this_node);
}

bool match_tree::is_complete() const
{
  return this->complete;
}

void match_tree::set_is_complete(bool comp)
{
  this->complete = comp;
}


} // namespace hext


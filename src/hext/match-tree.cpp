#include "hext/match-tree.h"


namespace hext {


match_tree::match_tree()
: children(),
  matches()
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

void match_tree::to_json(std::ostream& out) const
{
  if( !this->matches.empty() )
  {
    out << "{";
    assert(this->matches.size() > 0);
    std::vector<match_tree::name_value_pair>::const_iterator
      it_last = this->matches.end() - 1;
    for(auto it = this->matches.begin(); it != this->matches.end(); ++it)
    {
      out << it->first << ": \""
          << util::escape_quotes(it->second)
          << ( it == it_last ? "\"" : "\", " );
    }
    out << "}\n";
  }

  for(const auto& c : this->children)
  {
    c->to_json(out);
  }
}

void match_tree::print(std::ostream& out) const
{
  out << "digraph match_tree {\n";
  this->print_dot(out);
  out << "}\n";
}

void match_tree::print_dot(std::ostream& out, int parent_id) const
{
  static int node_index = 0;
  int this_node = ++node_index;

  std::string label;
  if( this->matches.empty() )
  {
    label.append("(empty)");
  }
  else
  {
    for(const auto& m : this->matches)
    {
      label.append(m.first);
      label.append(" ");
    }
  }

  out << "    node_" << this_node << " [label=\"" << label << "\"];\n"
      << "    node_" << parent_id << " -> node_"  << this_node << ";\n";

  for(const auto& c : this->children)
    c->print_dot(out, this_node);
}


} // namespace hext


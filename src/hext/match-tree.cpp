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

void match_tree::print(std::ostream& out, int indent_level) const
{
  std::string indent_str(indent_level * 2, ' ');

  out << indent_str
      << "match_tree matches: ";
  for(const auto& m : this->matches)
  {
    out << m.first << ": " << m.second << "; ";
  }

  out << "\n"
      << indent_str
      << "children("
      << this->children.size()
      << "):\n";

  for(const auto& c : this->children)
  {
    c->print(out, indent_level + 1);
  }
}


} // namespace hext


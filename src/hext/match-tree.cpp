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

match_tree::const_child_iterator match_tree::children_begin() const
{
  return this->children.begin();
}

match_tree::const_child_iterator match_tree::children_end() const
{
  return this->children.end();
}

std::vector<match_tree>::size_type match_tree::children_size() const
{
  return this->children.size();
}

match_tree::const_match_iterator match_tree::matches_begin() const
{
  return this->matches.begin();
}

match_tree::const_match_iterator match_tree::matches_end() const
{
  return this->matches.end();
}

void match_tree::to_json(std::ostream& out) const
{
  if( !this->matches.empty() )
  {
    out << "{";

    assert(this->matches.size() > 0);
    match_tree::const_match_iterator it_last = this->matches.end() - 1;
    for(auto it = this->matches.begin(); it != this->matches.end(); ++it)
    {
      out << it->first << ": \""
          << util::escape_quotes(it->second);

      if( it == it_last )
        out << "\"";
      else
        out << "\", ";
    }
    out << "}\n";
  }

  for(const auto& c : this->children)
  {
    c->to_json(out);
  }
}


} // namespace hext


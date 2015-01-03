#include "hext/match-tree.h"
#include "hext/rule.h"


namespace hext {


match_tree::match_tree()
: children(),
  matches(),
  r(nullptr)
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

void match_tree::set_rule(const rule * matching_rule)
{
  this->r = matching_rule;
}

void match_tree::print_json(std::ostream& out) const
{
  for(const auto& c : this->children)
  {
    out << "{";
    infix_ostream_iterator<std::string> it_out(out, ", ");
    this->print_json_matches(it_out);
    c->print_json_recursive(it_out);
    out << "}\n";
  }
}

void match_tree::print_dot(std::ostream& out) const
{
  out << "digraph match_tree {\n"
      << "    node [fontname=\"Arial\"];\n";
  this->print_dot_nodes(out);
  out << "}\n";
}

bool match_tree::filter()
{
  // TODO: explain why this step is neccessary
  if( this->children.size() == 1 && this->matches.empty() )
  {
    std::unique_ptr<match_tree> mt_front = std::move(this->children.front());
    // enable koenig lookup
    using namespace std;
    swap(this->r, mt_front->r);
    swap(this->children, mt_front->children);
  }

  // if the matching rule has no more children, we have a complete
  // match of a rule path, therefore we want to keep this branch by
  // returning false.
  if( this->r && this->r->children_size() == 0 )
    return false;

  for(auto& c : this->children)
  {
    if( c->filter() )
      c.reset(nullptr);
  }

  // erase all empty unique_ptr
  this->children.erase(
    std::remove(this->children.begin(), this->children.end(), nullptr),
    this->children.end()
  );

  // if there is no matching rule and there are no children, the branch
  // is non matching and must be removed
  if( this->r == nullptr )
    return this->children.empty();
  // there must be at least as many matches as there are child-rules,
  // if not, this branch is non matching and must be removed
  // TODO: can this break?
  else
    return this->r->children_size() > this->children.size();
}

void match_tree::print_json_recursive(
  infix_ostream_iterator<std::string>& out
) const
{
  this->print_json_matches(out);

  for(const auto& c : this->children)
    c->print_json_recursive(out);
}

void match_tree::print_json_matches(
  infix_ostream_iterator<std::string>& out
) const
{
  for(const auto& p : this->matches)
  {
    std::string str("\"");
    str.append(util::escape_quotes(p.first))
       .append("\": \"")
       .append(util::escape_quotes(p.second))
       .append("\"");
    out = str;
  }
}

void match_tree::print_dot_nodes(std::ostream& out, int parent_id) const
{
  static int node_index = 0;
  int this_node = ++node_index;

  std::string label;
  if( this->r == nullptr || this->r->get_tag_name().empty() )
    label.append("[rule]");
  else
    label.append(this->r->get_tag_name());

  for(const auto& m : this->matches)
  {
    label.append(" ");
    label.append(m.first);
  }

  if( this->r && this->r->children_size() == 0 )
    label.append("*");

  out << "    node_" << this_node << " [label=\"" << label << "\"];\n";
  if( parent_id )
    out << "    node_" << parent_id << " -> node_" << this_node << ";\n";

  for(const auto& c : this->children)
    c->print_dot_nodes(out, this_node);
}


} // namespace hext


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
    rapidjson::Document json;
    json.SetObject();

    this->append_json_matches(json);
    c->append_json_recursive(json);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    json.Accept(writer);
    out << buffer.GetString() << "\n";
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
  // if the matching rule has no more children, we have a complete
  // match of a rule path, therefore we want to keep this branch by
  // returning false.
  if( this->r && this->r->children_size() == 0 )
    return false;

  for(auto& c : this->children)
    if( c->filter() )
      c.reset(nullptr);

  // erase all empty unique_ptr
  this->children.erase(
    std::remove(this->children.begin(), this->children.end(), nullptr),
    this->children.end()
  );

  // if there is no matching rule and there are no children, the branch
  // is non matching and must be removed
  if( !this->r )
    return this->children.empty();

  // keep
  return false;
}

void match_tree::append_json_recursive(rapidjson::Document& json) const
{
  this->append_json_matches(json);

  for(const auto& c : this->children)
    c->append_json_recursive(json);
}

void match_tree::append_json_matches(rapidjson::Document& json) const
{
  rapidjson::Document::AllocatorType& allocator = json.GetAllocator();
  for(const auto& p : this->matches)
  {
    rapidjson::Value name(p.first.c_str(), allocator);
    rapidjson::Value value(p.second.c_str(), allocator);
    // If the key is already taken, transform the value into an array
    if( json.HasMember(name) )
    {
      if( json[name].IsArray() )
      {
        json[name].PushBack(value, allocator);
      }
      else
      {
        rapidjson::Value array(rapidjson::kArrayType);
        array.PushBack(json[name], allocator);
        array.PushBack(value, allocator);
        json[name] = array;
      }
    }
    else
    {
      json.AddMember(name, value, allocator);
    }
  }
}

void match_tree::print_dot_nodes(std::ostream& out, int parent_id) const
{
  static int node_index = 0;
  int this_node = ++node_index;

  std::string label;
  if( !this->r || this->r->tag_name().empty() )
    label.append("[rule]");
  else
    label.append(this->r->tag_name());

  for(const auto& m : this->matches)
  {
    label.append(" ");
    label.append(m.first);
  }

  if( this->r && this->r->is_direct_descendant() )
    label.append("!");

  out << "    node_" << this_node << " [label=\"" << label << "\"];\n";
  if( parent_id )
    out << "    node_" << parent_id << " -> node_" << this_node << ";\n";

  for(const auto& c : this->children)
    c->print_dot_nodes(out, this_node);
}


} // namespace hext


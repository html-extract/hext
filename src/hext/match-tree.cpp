#include "hext/match-tree.h"
#include "hext/rule.h"


namespace hext {


MatchTree::MatchTree()
: children_(),
  matches_(),
  r_(nullptr)
{
}

MatchTree * MatchTree::append_child_and_own(std::unique_ptr<MatchTree> m)
{
  this->children_.push_back(std::move(m));
  return this->children_.back().get();
}

void MatchTree::append_match(const NameValuePair& p)
{
  this->matches_.push_back(p);
}

void MatchTree::set_rule(const Rule * matching_rule)
{
  this->r_ = matching_rule;
}

void MatchTree::print_json(std::ostream& out) const
{
  for(const auto& c : this->children_)
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

void MatchTree::print_dot(std::ostream& out) const
{
  out << "digraph match_tree {\n"
      << "    node [fontname=\"Arial\"];\n";
  this->print_dot_nodes(out);
  out << "}\n";
}

bool MatchTree::filter()
{
  // depth first
  for(auto& c : this->children_)
    if( c->filter() )
      c.reset(nullptr);

  // erase all empty unique_ptr
  this->children_.erase(
    std::remove(this->children_.begin(), this->children_.end(), nullptr),
    this->children_.end()
  );

  // Check if all rules are present in this match-tree.
  if( this->r_ )
  {
    auto c_begin = this->children_.begin();
    auto c_end = this->children_.end();
    for(const auto& rl : this->r_->get_children())
    {
      // If there are no more match-branches, all rules that follow must
      // be optional.
      if( c_begin == c_end )
      {
        if( !rl.optional() )
          return true;
      }
      // match-branches and rule-children have the same order.
      // Check if child has this rule.
      else if( *c_begin && (*c_begin)->r_ == &rl )
      {
        c_begin++;
      }
      // Optional rules can be omitted
      else if( !rl.optional() )
      {
        return true;
      }
    }
  }

  // keep
  return false;
}

void MatchTree::append_json_recursive(rapidjson::Document& json) const
{
  this->append_json_matches(json);

  for(const auto& c : this->children_)
    c->append_json_recursive(json);
}

void MatchTree::append_json_matches(rapidjson::Document& json) const
{
  rapidjson::Document::AllocatorType& allocator = json.GetAllocator();
  for(const auto& p : this->matches_)
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

void MatchTree::print_dot_nodes(std::ostream& out, int parent_id) const
{
  static int node_index = 0;
  int this_node = ++node_index;

  std::string label;
  if( !this->r_ || this->r_->tag_name().empty() )
    label.append("[rule]");
  else
    label.append(this->r_->tag_name());

  for(const auto& m : this->matches_)
  {
    label.append(" ");
    label.append(m.first);
  }

  out << "    node_" << this_node << " [label=\"" << label << "\"];\n";
  if( parent_id )
    out << "    node_" << parent_id << " -> node_" << this_node << ";\n";

  for(const auto& c : this->children_)
    c->print_dot_nodes(out, this_node);
}


} // namespace hext


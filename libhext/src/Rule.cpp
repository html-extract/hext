#include "hext/Rule.h"


namespace hext {


Rule::Rule(
  GumboTag tag,
  bool optional,
  bool any_descendant
)
: children_()
, match_patterns_()
, capture_patterns_()
, tag_(tag)
, is_optional_(optional)
, is_any_descendant_(any_descendant)
{
}

void Rule::append_child(Rule&& r, std::size_t tree_depth)
{
  if( tree_depth > 0 && !this->children_.empty() )
  {
    this->children_.back().append_child(std::move(r), tree_depth - 1);
    return;
  }

  this->children_.push_back(std::move(r));
}

std::unique_ptr<ResultTree> Rule::extract(const GumboNode * node) const
{
  auto rt = MakeUnique<ResultTree>();

  if( this->children_.size() == 1 )
  {
    auto first_child = this->children_.begin();
    if( first_child->matches(node) )
    {
      auto values = first_child->capture(node);
      auto child_rt = rt->create_branch(values);
      if( !first_child->extract_children(node, child_rt) )
        rt->delete_branch(child_rt);
      return std::move(rt);
    }
  }

  this->extract_children(node, rt.get());
  return std::move(rt);
}

bool Rule::matches(const GumboNode * node) const
{
  if( !node )
    return false;

  if( this->tag_ != GUMBO_TAG_UNKNOWN )
    if( node->type != GUMBO_NODE_ELEMENT ||
        node->v.element.tag != this->tag_ )
      return false;

  for(const auto& pattern : this->match_patterns_)
    if( !pattern->matches(node) )
      return false;

  return true;
}

std::vector<ResultPair> Rule::capture(const GumboNode * node) const
{
  if( !node )
    return std::vector<ResultPair>();

  std::vector<ResultPair> values;
  values.reserve(this->capture_patterns_.size());
  for(const auto& pattern : this->capture_patterns_ )
    values.push_back(pattern->capture(node));

  return values;
}

bool Rule::extract_children(const GumboNode * node, ResultTree * rt) const
{
  if( !node || !rt )
    return false;

  if( this->children_.empty() )
    return true;

  if( node->type != GUMBO_NODE_ELEMENT )
    return false;

  int match_count = 0;
  const GumboVector * child_nodes = &node->v.element.children;
  std::size_t mandatory_rule_cnt = std::count_if(
    this->children_.cbegin(),
    this->children_.cend(),
    [](const Rule& r) { return !r.is_optional_; }
  );
  MatchContext mc(
    this->children_.cbegin(),
    this->children_.cend(),
    child_nodes,
    mandatory_rule_cnt
  );
  while( auto grouped_match = mc.match_next() )
  {
    ++match_count;
    auto branch = rt->create_branch();
    for( const auto& match_pair : *grouped_match )
    {
      const Rule * child_rule = match_pair.first;
      const GumboNode * child_node = match_pair.second;
      assert(child_rule && child_node);

      auto values = child_rule->capture(child_node);
      auto child_rt = branch->create_branch(values);

      if( !child_rule->extract_children(child_node, child_rt) )
      {
        rt->delete_branch(branch);
        --match_count;
        break;
      }
    }
  }

  if( this->is_any_descendant_ )
  {
    const GumboVector * node_children = &node->v.element.children;
    for(unsigned int i = 0; i < node_children->length; ++i)
    {
      auto child_node = static_cast<const GumboNode *>(node_children->data[i]);
      this->extract_children(child_node, rt);
    }
  }

  return !mandatory_rule_cnt || match_count > 0;
}


} // namespace hext


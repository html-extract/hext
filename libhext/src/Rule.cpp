#include "hext/Rule.h"
#include "hext/ResultTree.h"


namespace hext {


Rule::Rule(
  GumboTag tag,
  bool is_optional,
  bool is_any_descendant,
  std::vector<std::unique_ptr<MatchPattern>>&& match_patterns,
  std::vector<std::unique_ptr<CapturePattern>>&& capture_patterns
)
: children_()
, match_patterns_(std::move(match_patterns))
, capture_patterns_(std::move(capture_patterns))
, gumbo_tag_(tag)
, is_optional_(is_optional)
, is_any_descendant_(is_any_descendant)
{
}

void Rule::append_child(Rule&& r, std::size_t level)
{
  if( level > 0 && !this->children_.empty() )
  {
    this->children_.back().append_child(std::move(r), level - 1);
    return;
  }

  this->children_.push_back(std::move(r));
}

bool Rule::optional() const
{
  return this->is_optional_;
}

std::unique_ptr<ResultTree> Rule::extract(const GumboNode * node) const
{
  auto rt = MakeUnique<ResultTree>(nullptr);
  this->extract_top(node, rt.get());
  return std::move(rt);
}

bool Rule::matches(const GumboNode * node) const
{
  if( !node )
    return false;

  if( this->gumbo_tag_ != GUMBO_TAG_UNKNOWN )
    if( node->type != GUMBO_NODE_ELEMENT ||
        node->v.element.tag != this->gumbo_tag_ )
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

bool Rule::extract_top(const GumboNode * node, ResultTree * rt) const
{
  if( !node || !rt )
    return false;

  if( node->type != GUMBO_NODE_ELEMENT )
    return false;

  if( this->children_.empty() )
    return true;

  int match_count = 0;
  const GumboVector * child_nodes = &node->v.element.children;
  MatchContext mc(
    this->children_.cbegin(),
    this->children_.cend(),
    child_nodes
  );
  while( auto grouped_match = mc.match_next() )
  {
    ++match_count;
    auto branch = rt->create_branch(nullptr, std::vector<ResultPair>());
    for( const auto& match_pair : *grouped_match )
    {
      const Rule * child_rule = match_pair.first;
      const GumboNode * child_node = match_pair.second;
      assert(child_rule && child_node);
      auto child_rt = branch->create_branch(
        child_rule,
        child_rule->capture(child_node)
      );
      if( !child_rule->extract_top(child_node, child_rt) )
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
      this->extract_top(child_node, rt);
    }
  }

  return match_count > 0;
}


} // namespace hext


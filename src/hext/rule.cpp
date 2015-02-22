#include "hext/rule.h"
#include "hext/match-tree.h"


namespace hext {


Rule::Rule(
  const std::string& html_tag_name,
  bool is_optional,
  bool direct_descendant,
  bool closed,
  unsigned int nth_child,
  RulePatterns&& r_patterns
)
: children()
, patterns(std::move(r_patterns))
, match_count(0)
, gumbo_tag(gumbo_tag_enum(html_tag_name.c_str()))
, tag(html_tag_name)
, is_opt(is_optional)
, is_direct_desc(direct_descendant)
, is_closed(closed)
, child_pos(nth_child)
{
}

Rule::~Rule()
{
}

Rule::Rule(Rule&& r)
: children(std::move(r.children))
, patterns(std::move(r.patterns))
, match_count(r.match_count.load())
, gumbo_tag(r.gumbo_tag)
, tag(std::move(r.tag))
, is_opt(r.is_opt)
, is_direct_desc(r.is_direct_desc)
, is_closed(r.is_closed)
, child_pos(r.child_pos)
{
}

void Rule::append_child(Rule&& r, int level)
{
  if( level > 1 && !this->children.empty() )
  {
    this->children.back().append_child(std::move(r), level - 1);
    return;
  }

  this->children.push_back(std::move(r));
}

const std::vector<Rule>& Rule::get_children() const
{
  return this->children;
}

std::string Rule::tag_name() const
{
  return this->tag;
}

bool Rule::optional() const
{
  return this->is_opt;
}

void Rule::extract(const GumboNode * node, MatchTree * m) const
{
  if( !node || !m || node->type != GUMBO_NODE_ELEMENT )
    return;

  if( this->matches(node) )
  {
    this->match_count++;

    // Although we have a match, this may not be the html-node that the user
    // is searching for, so we have to keep matching.
    this->extract_node_children(node, m);

    {
      std::unique_ptr<MatchTree> mt = this->patterns.capture(node);
      assert(mt != nullptr);
      mt->set_rule(this);
      m = m->append_child_and_own(std::move(mt));
    }

    for(const auto& c : this->children)
      c.extract_node_children(node, m);
  }
  else
  {
    // if this rule is a direct descendant, and it didn't match,
    // all child-rules cannot be matched either.
    if( !this->is_direct_desc )
      this->extract_node_children(node, m);
  }
}

void Rule::print(
  std::ostream& out,
  int indent_level,
  bool print_match_count
) const
{
  if( print_match_count )
    out << "\tx" << this->match_count << " |";

  out << ( indent_level ? std::string(indent_level * 2, ' ') : "" )
      << "<"
      << ( this->is_opt ? "?" : "" )
      << ( this->is_direct_desc ? "!" : "" );

  if( this->child_pos > 0 )
    out << this->child_pos;

  out << this->tag;

  this->patterns.print(out);

  if( this->is_closed )
    out << ">";

  out << "\n";
  for(const auto& c : this->children)
    c.print(out, indent_level + 1, print_match_count);
}

bool Rule::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  // empty tag-name matches every tag
  if( !this->tag.empty() )
    if( node->v.element.tag != this->gumbo_tag )
      return false;

  if( this->child_pos > 0 )
  {
    unsigned int pos = Rule::get_node_position_within_parent(node);
    if( pos != this->child_pos )
      return false;
  }

  if( this->is_closed )
    return this->patterns.matches_all_attributes(node);
  else
    return this->patterns.matches(node);
}

void Rule::extract_node_children(const GumboNode * node, MatchTree * m) const
{
  if( !node || !m || node->type != GUMBO_NODE_ELEMENT )
    return;

  const GumboVector * node_children = &node->v.element.children;
  for(unsigned int i = 0; i < node_children->length; ++i)
  {
    this->extract(
      static_cast<const GumboNode *>(node_children->data[i]),
      m
    );
  }
}

unsigned int
Rule::get_node_position_within_parent(const GumboNode * node) const
{
  if( !node )
    return 0;

  const GumboNode * parent = node->parent;

  if( !parent || parent->type != GUMBO_NODE_ELEMENT )
    return 0;

  unsigned int pos = 0;
  const GumboVector& child_nodes = parent->v.element.children;
  // We only have to traverse up to node->index_within_parent, and not the
  // whole GumboVector.
  for(unsigned int i = 0; i <= node->index_within_parent; ++i)
  {
    assert(i < child_nodes.length);
    const GumboNode * child = 
      static_cast<const GumboNode *>(child_nodes.data[i]);

    if( child && child->type == GUMBO_NODE_ELEMENT )
      ++pos;

    if( node == child )
      return pos;
  }

  return 0;
}


} // namespace hext


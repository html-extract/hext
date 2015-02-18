#include "hext/rule.h"
#include "hext/match-tree.h"


namespace hext {


rule::rule(
  const std::string& html_tag_name,
  bool direct_descendant,
  bool closed,
  unsigned int nth_child,
  rule_patterns&& r_patterns
)
: children()
, patterns(std::move(r_patterns))
, match_count(0)
, tag(html_tag_name)
, is_direct_desc(direct_descendant)
, is_closed(closed)
, child_pos(nth_child)
{
}

rule::rule(rule&& r)
: children(std::move(r.children))
, patterns(std::move(r.patterns))
, match_count(r.match_count.load())
, tag(std::move(r.tag))
, is_direct_desc(r.is_direct_desc)
, is_closed(r.is_closed)
, child_pos(r.child_pos)
{
}

void rule::append_child(rule&& r, int level)
{
  if( level > 1 && !this->children.empty() )
  {
    this->children.back().append_child(std::move(r), level - 1);
    return;
  }

  this->children.push_back(std::move(r));
}

std::vector<rule>::size_type rule::children_size() const
{
  return this->children.size();
}

std::string rule::tag_name() const
{
  return this->tag;
}

bool rule::is_direct_descendant() const
{
  return this->is_direct_desc;
}

void rule::extract(const GumboNode * node, match_tree * m) const
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
      std::unique_ptr<match_tree> mt = this->patterns.capture(node);
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

void rule::print(
  std::ostream& out,
  int indent_level,
  bool print_match_count
) const
{
  if( print_match_count )
    out << "\tx" << this->match_count << " |";

  out << ( indent_level ? std::string(indent_level * 2, ' ') : "" )
      << "<"
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

bool rule::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  // empty tag-name matches every tag
  if( !this->tag.empty() )
    if( node->v.element.tag != gumbo_tag_enum(this->tag.c_str()) )
      return false;

  if( this->child_pos > 0 )
  {
    unsigned int pos = rule::get_node_position_within_parent(node);
    if( pos != this->child_pos )
      return false;
  }

  if( this->is_closed )
    return this->patterns.matches_all_attributes(node);
  else
    return this->patterns.matches(node);
}

void rule::extract_node_children(const GumboNode * node, match_tree * m) const
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
rule::get_node_position_within_parent(const GumboNode * node) const
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


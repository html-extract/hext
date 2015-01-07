#include "hext/rule.h"
#include "hext/match-tree.h"


namespace hext {


rule::rule(
  const std::string& html_tag_name,
  bool direct_descendant,
  int max_capture_limit,
  std::vector<attribute>&& attrs
)
: children(),
  attributes(std::move(attrs)),
  tag(html_tag_name),
  is_direct_desc(direct_descendant),
  cap_limit(max_capture_limit),
  match_count(0)
{
}

rule::rule(const rule& r)
: children(r.children),
  attributes(r.attributes),
  tag(r.tag),
  is_direct_desc(r.is_direct_desc),
  cap_limit(r.cap_limit),
  match_count(0)
{
}

void rule::append_child(const rule& r, int level)
{
  if( level > 1 && !this->children.empty() )
  {
    this->children.back().append_child(r, level - 1);
    return;
  }

  this->children.push_back(r);
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

int rule::capture_limit() const
{
  return this->cap_limit;
}

void rule::match(const GumboNode * node, match_tree * m) const
{
  if( !node || !m || node->type != GUMBO_NODE_ELEMENT )
    return;

  if( this->matches(node) )
  {
    this->match_count++;
    m = m->append_child_and_own(this->capture(node));

    for(const auto& c : this->children)
    {
      if( c.cap_limit == 0 || c.match_count < c.cap_limit )
        c.match_node_children(node, m);
    }
  }
  else
  {
    // if this rule is a direct descendant, and it didn't match,
    // all child-rules cannot be matched either.
    if( !this->is_direct_desc )
      if( this->cap_limit == 0 || this->match_count < this->cap_limit )
        this->match_node_children(node, m);
  }
}

void rule::print(std::ostream& out, int indent_level) const
{
  out << ( indent_level ? std::string(indent_level * 2, ' ') : "" )
      << "<"
      << this->tag
      << " ";

  for(const auto& a : this->attributes)
  {
    a.print(out);
    out << " ";
  }

  out << ">\n";
  for(const auto& c : this->children)
    c.print(out, indent_level + 1);
}

std::unique_ptr<match_tree>
rule::capture(const GumboNode * node) const
{
  std::unique_ptr<match_tree> m_node = make_unique<match_tree>();
  m_node->set_rule(this);

  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return m_node;

  for(const auto& attr : this->attributes)
    if( attr.is_capture() )
      m_node->append_match(attr.capture(node));

  return m_node;
}

bool rule::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  if( !this->tag.empty() &&
      node->v.element.tag != gumbo_tag_enum(this->tag.c_str()) )
    return false;

  for(const auto& attr : this->attributes)
  {
    if( !attr.matches(node) )
      return false;
  }

  return true;
}

void rule::match_node_children(const GumboNode * node, match_tree * m) const
{
  if( !node || !m || node->type != GUMBO_NODE_ELEMENT )
    return;

  const GumboVector * node_children = &node->v.element.children;
  for(unsigned int i = 0; i < node_children->length; ++i)
  {
    this->match(
      static_cast<const GumboNode *>(node_children->data[i]),
      m
    );
  }
}


} // namespace hext


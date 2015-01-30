#include "hext/rule.h"
#include "hext/match-tree.h"


namespace hext {


rule::rule(
  const std::string& html_tag_name,
  bool direct_descendant,
  bool closed,
  int max_capture_limit,
  std::vector<std::unique_ptr<match_pattern>>&& matchp,
  std::vector<std::unique_ptr<capture_pattern>>&& capturep
)
: children()
, match_patterns(std::move(matchp))
, capture_patterns(std::move(capturep))
, tag(html_tag_name)
, is_direct_desc(direct_descendant)
, is_closed(closed)
, cap_limit(max_capture_limit)
, match_count(0)
{
}

rule::rule(rule&& r)
: children(std::move(r.children))
, match_patterns(std::move(r.match_patterns))
, capture_patterns(std::move(r.capture_patterns))
, tag(std::move(r.tag))
, is_direct_desc(r.is_direct_desc)
, is_closed(r.is_closed)
, cap_limit(r.cap_limit)
, match_count(0)
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

void rule::match(const GumboNode * node, match_tree * m) const
{
  if( !node || !m || node->type != GUMBO_NODE_ELEMENT )
    return;

  if( this->matches(node) )
  {
    this->match_count++;

    {
      std::unique_ptr<match_tree> mt = this->capture(node);
      // If this rule has branches, then the match_tree must also branch.
      // But if we have captured content, we must add a branch anyway.
      if( this->children.size() > 1 || !mt->matches_empty() )
        m = m->append_child_and_own(std::move(mt));
    }

    for(const auto& c : this->children)
      if( c.cap_limit == 0 || c.match_count < c.cap_limit )
        c.match_node_children(node, m);
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
      << ( this->is_direct_desc ? "!" : "" );

  if( this->cap_limit > 0 )
    out << this->cap_limit;

  out << this->tag
      << " ";

  for(const auto& p : this->match_patterns)
    p->print(out);

  for(const auto& p : this->capture_patterns)
    p->print(out);

  if( this->is_closed )
    out << ">";

  out << "\n";
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

  for(const auto& pattern : this->capture_patterns)
    m_node->append_match(pattern->capture(node));

  return m_node;
}

bool rule::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  // empty tag-name matches every tag
  if( !this->tag.empty() )
    if( node->v.element.tag != gumbo_tag_enum(this->tag.c_str()) )
      return false;

  std::vector<const GumboAttribute *> m_attrs;
  for(const auto& pattern : this->match_patterns)
  {
    match_result mr = pattern->matches(node);
    if( mr.first /* bool is matching? */ )
    {
      if( /* const GumboAttribute* */ mr.second /* != nullptr */ )
        m_attrs.push_back(mr.second);
    }
    else
    {
      return false;
    }
  }

  if( this->is_closed )
  {
    // if the rule is closed, we have to have matched all attributes
    const GumboVector& attr = node->v.element.attributes;
    for(unsigned int i = 0; i < attr.length; ++i)
      if( std::find(m_attrs.begin(), m_attrs.end(), attr.data[i]) == m_attrs.end() )
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


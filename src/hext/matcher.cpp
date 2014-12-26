#include "hext/matcher.h"


namespace hext {


matcher::match_error::match_error(const char * msg)
: std::runtime_error(msg)
{
}


matcher::matcher(const char * path)
: g_outp(nullptr),
  buffer()
{
  assert(path != nullptr);

  {
    std::ifstream file;
    // force exception on error
    file.exceptions(std::ios::failbit | std::ios::badbit);
    file.open(path);

    std::stringstream stream;
    stream << file.rdbuf();

    this->buffer = stream.str();

    file.close();
  }

  this->g_outp = gumbo_parse(this->buffer.c_str());
  if( this->g_outp == nullptr )
    throw match_error("gumbo_parse returned nullptr");
}

std::unique_ptr<match_tree>
matcher::capture_node(const rule * r, const GumboNode * node) const
{
  typedef rule::const_attribute_iterator r_attr_iter;

  std::unique_ptr<match_tree> m_node = make_unique<match_tree>();

  if( r == nullptr )
    return m_node;

  if( node == nullptr )
    return m_node;

  if( node->type != GUMBO_NODE_ELEMENT )
    return m_node;

  for(r_attr_iter it = r->attributes_begin(); it != r->attributes_end(); ++it)
  {
    if( it->is_capture() )
    {
      m_node->append_match(
        this->capture_attribute(&(*it), node)
      );
    }
  }

  return m_node;
}

match_tree::name_value_pair
matcher::capture_attribute(const attribute * a, const GumboNode * node) const
{
  if( a == nullptr )
    return match_tree::name_value_pair("", "");

  if( node == nullptr )
    return match_tree::name_value_pair("", "");

  if( node->type != GUMBO_NODE_ELEMENT )
    return match_tree::name_value_pair("", "");

  if( a->get_name() == "hext-inner-text" )
  {
    return match_tree::name_value_pair(
      /* name  */ a->get_value(),
      /* value */ bc::capture_inner_text(node)
    );
  }
  else
  {
    GumboAttribute * g_attr = gumbo_get_attribute(
      &node->v.element.attributes,
      a->get_name().c_str()
    );
    return match_tree::name_value_pair(
      /* name  */ a->get_value(),
      /* value */ ( g_attr && g_attr->value ? g_attr->value : "" )
    );
  }
}

bool matcher::node_matches_rule(const GumboNode * node, const rule * r) const
{
  typedef rule::const_attribute_iterator r_attr_iter;

  if( node == nullptr )
    return false;

  if( r == nullptr )
    return false;

  if( node->type != GUMBO_NODE_ELEMENT )
    return false;

  std::string tag_name = r->get_tag_name();
  if( !tag_name.empty() &&
      node->v.element.tag != gumbo_tag_enum(tag_name.c_str()) )
    return false;

  for(r_attr_iter it = r->attributes_begin(); it != r->attributes_end(); ++it)
  {
    std::string attr_name = it->get_name();

    GumboAttribute * g_attr =
      gumbo_get_attribute(&node->v.element.attributes, attr_name.c_str());
    if( !g_attr && !it->is_builtin() )
      return false;

    std::string attr_value = it->get_value();
    if( !it->is_capture() && !attr_value.empty() )
    {
      if( attr_value.compare(g_attr->value) != 0 )
        return false;
    }
  }

  return true;
}

std::unique_ptr<match_tree> matcher::match(const rule * r) const
{
  assert(this->g_outp != nullptr);
  assert(r != nullptr);
  std::unique_ptr<match_tree> m = make_unique<match_tree>();
  if( r )
    this->match_node(r, this->g_outp->root, m.get());
  return m;
}

void matcher::match_node(
  const rule * r,
  const GumboNode * node,
  match_tree * m
) const
{
  typedef rule::const_child_iterator r_child_iter;

  if( r == nullptr )
    return;

  if( node == nullptr )
    return;

  if( m == nullptr )
    return;

  if( node->type != GUMBO_NODE_ELEMENT )
    return;

  if( this->node_matches_rule(node, r) )
  {
    m = m->append_child_and_own(this->capture_node(r, node));

    for(r_child_iter it = r->children_begin(); it != r->children_end(); ++it)
    {
      this->match_node_children(&(*it), node, m);
    }
  }
  else
  {
    this->match_node_children(r, node, m);
  }
}

void matcher::match_node_children(
  const rule * r,
  const GumboNode * node,
  match_tree * m
) const
{
  if( r == nullptr )
    return;

  if( node == nullptr )
    return;

  if( m == nullptr )
    return;

  if( node->type != GUMBO_NODE_ELEMENT )
    return;

  const GumboVector * children = &node->v.element.children;
  for(unsigned int i = 0; i < children->length; ++i)
  {
    this->match_node(r, static_cast<const GumboNode *>(children->data[i]), m);
  }
}

matcher::~matcher()
{
  assert(this->g_outp != nullptr);
  gumbo_destroy_output(&kGumboDefaultOptions, this->g_outp);
}


} // namespace hext


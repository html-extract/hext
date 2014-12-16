#ifndef HEXT_MATCHER_H
#define HEXT_MATCHER_H

#include <cassert>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "gumbo.h"

#include "hext/rule.h"
#include "hext/attribute.h"
#include "hext/match_tree.h"


namespace hext {


class matcher
{
public:
  class match_error : public std::runtime_error
  {
  public:
    match_error(const char * msg)
    : std::runtime_error(msg) {}
  };

  matcher(const char * path)
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

  match_tree capture_node(const rule& r, const GumboNode * node) const
  {
    typedef rule::const_attribute_iterator r_attr_iter;

    match_tree m_node;

    if( node == nullptr )
      return m_node;

    if( node->type != GUMBO_NODE_ELEMENT )
      return m_node;

    for(r_attr_iter it = r.attributes_begin(); it != r.attributes_end(); ++it)
    {
      if( it->get_is_capture() )
      {
        GumboAttribute * g_attr = gumbo_get_attribute(
          &node->v.element.attributes,
          it->get_name().c_str()
        );
        m_node.append_match(
          /* name  */ it->get_name(),
          /* value */ ( g_attr ? g_attr->value : nullptr )
        );
      }
    }

    return m_node;
  }

  void match_node(const rule& r, const GumboNode * node, match_tree * m) const
  {
    typedef rule::const_child_iterator r_child_iter;

    if( node == nullptr )
      return;

    if( m == nullptr )
      return;

    if( node->type != GUMBO_NODE_ELEMENT )
      return;

    if( this->node_matches_rule(node, r) )
    {
      match_tree m_node = this->capture_node(r, node);
      m = &m->append_child(m_node);

      for(r_child_iter it = r.children_begin(); it != r.children_end(); ++it)
      {
        this->match_node_children(*it, node, m);
      }
    }
    else
    {
      this->match_node_children(r, node, m);
    }
  }

  void match_node_children(const rule& r, const GumboNode * node, match_tree * m) const
  {
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

  bool node_matches_rule(const GumboNode * node, const rule& r) const
  {
    typedef rule::const_attribute_iterator r_attr_iter;

    if( node == nullptr )
      return false;

    if( node->type != GUMBO_NODE_ELEMENT )
      return false;

    std::string tag_name = r.get_tag_name();
    if( node->v.element.tag != gumbo_tag_enum(tag_name.c_str()) )
    {
      return false;
    }

    for(r_attr_iter it = r.attributes_begin(); it != r.attributes_end(); ++it)
    {
      std::string attr_name = it->get_name();
      GumboAttribute * g_attr = gumbo_get_attribute(&node->v.element.attributes, attr_name.c_str());
      if( !g_attr )
      {
        return false;
      }

      std::string attr_value = it->get_value();
      if( !it->get_is_capture() && !attr_value.empty() )
      {
        if( attr_value.compare(g_attr->value) != 0 )
          return false;
      }
    }

    return true;
  }

  match_tree match(const rule& r) const
  {
    match_tree m;
    this->match_node(r, this->g_outp->root, &m);
    return m;
  }

  ~matcher()
  {
    assert(this->g_outp != nullptr);
    gumbo_destroy_output(&kGumboDefaultOptions, this->g_outp);
  }

  matcher(const matcher&) = delete;
  matcher& operator=(const matcher&) = delete;

private:
  GumboOutput * g_outp;
  std::string buffer;
};


} // namespace hext


#endif // HEXT_MATCHER_H


#ifndef HEXT_MATCHER_H
#define HEXT_MATCHER_H

#include <cassert>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <queue>
#include <tuple>

#include <gumbo.h>

#include "hext/rule.h"
#include "hext/attribute.h"
#include "hext/match_tree.h"
#include "hext/make-unique.h"


namespace hext {


class matcher
{
  typedef std::tuple<
    const rule *,
    const GumboNode *,
    match_tree *
  > match_context;

public:
  class match_error : public std::runtime_error
  {
  public:
    explicit match_error(const char * msg)
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

  std::unique_ptr<match_tree> capture_node(const rule& r, const GumboNode * node) const
  {
    typedef rule::const_attribute_iterator r_attr_iter;

    std::unique_ptr<match_tree> m_node = make_unique<match_tree>();

    if( node == nullptr )
      return m_node;

    if( node->type != GUMBO_NODE_ELEMENT )
      return m_node;

    for(r_attr_iter it = r.attributes_begin(); it != r.attributes_end(); ++it)
    {
      if( it->get_is_capture() )
      {
        m_node->append_match(
          this->capture_attribute(*it, node)
        );
      }
    }

    return m_node;
  }

  match_tree::name_value_pair
  capture_attribute(const attribute& a, const GumboNode * node) const
  {
    assert(node != nullptr);
    assert(node->type == GUMBO_NODE_ELEMENT);

    GumboAttribute * g_attr = gumbo_get_attribute(
      &node->v.element.attributes,
      a.get_name().c_str()
    );
    return match_tree::name_value_pair(
      /* name  */ a.get_value(),
      /* value */ ( g_attr && g_attr->value ? g_attr->value : "" )
    );
  }

  std::unique_ptr<match_tree>
  match_node_bfs(const rule& rul, const GumboNode * nod) const
  {
    typedef rule::const_child_iterator r_child_iter;

    std::unique_ptr<match_tree> m_root = make_unique<match_tree>();

    if( nod == nullptr )
      return m_root;

    if( nod->type != GUMBO_NODE_ELEMENT )
      return m_root;

    std::queue<match_context> q;
    q.push(std::make_tuple(&rul, nod, m_root.get()));

    while( !q.empty() )
    {
      match_context mc = q.front();
      q.pop();

      const rule *      r    = std::get<0>(mc);
      const GumboNode * node = std::get<1>(mc);
      match_tree *      m    = std::get<2>(mc);

      assert(r          != nullptr);
      assert(node       != nullptr);
      assert(m          != nullptr);
      assert(node->type == GUMBO_NODE_ELEMENT);

      if( this->node_matches_rule(node, r) )
      {
        match_tree * m_node = m->append_child_and_own(
          this->capture_node(*r, node)
        );

        for(r_child_iter it = r->children_begin(); it != r->children_end(); ++it)
        {
          const GumboVector * children = &node->v.element.children;
          for(unsigned int i = 0; i < children->length; ++i)
          {
            const GumboNode * child_node =
              static_cast<const GumboNode *>(children->data[i]);

            assert(child_node != nullptr);

            if( child_node->type == GUMBO_NODE_ELEMENT )
            {
              q.push(
                std::make_tuple(&(*it), child_node, m_node)
              );
            }
          }
        }
      }
      else if( r->get_is_direct_descendant() )
      {
        // if the rule only matches direct descendants,
        // but we didn't find a match on this level,
        // we can skip the rule and all its children
        // (by not pushing child-rules into the queue)
        continue;
      }

      {
        const GumboVector * children = &node->v.element.children;
        for(unsigned int i = 0; i < children->length; ++i)
        {
          const GumboNode * child_node =
            static_cast<const GumboNode *>(children->data[i]);

          assert(child_node != nullptr);

          if( child_node->type == GUMBO_NODE_ELEMENT )
          {
            q.push(
              std::make_tuple(r, child_node, m)
            );
          }
        }
      }
    }

    return m_root;
  }

  bool node_matches_rule(const GumboNode * node, const rule * r) const
  {
    typedef rule::const_attribute_iterator r_attr_iter;

    if( node == nullptr )
      return false;

    if( r == nullptr )
      return false;

    if( node->type != GUMBO_NODE_ELEMENT )
      return false;

    std::string tag_name = r->get_tag_name();
    if( node->v.element.tag != gumbo_tag_enum(tag_name.c_str()) )
      return false;

    for(r_attr_iter it = r->attributes_begin(); it != r->attributes_end(); ++it)
    {
      std::string attr_name = it->get_name();

      GumboAttribute * g_attr =
        gumbo_get_attribute(&node->v.element.attributes, attr_name.c_str());
      if( !g_attr )
        return false;

      std::string attr_value = it->get_value();
      if( !it->get_is_capture() && !attr_value.empty() )
      {
        if( attr_value.compare(g_attr->value) != 0 )
          return false;
      }
    }

    return true;
  }

  std::unique_ptr<match_tree> match_bfs(const rule& r) const
  {
    assert(this->g_outp != nullptr);
    return this->match_node_bfs(r, this->g_outp->root);
  }

  ~matcher()
  {
    assert(this->g_outp != nullptr);
    gumbo_destroy_output(&kGumboDefaultOptions, this->g_outp);
  }

private:
  matcher(const matcher&) = delete;
  matcher& operator=(const matcher&) = delete;

  GumboOutput * g_outp;
  std::string buffer;
};


} // namespace hext


#endif // HEXT_MATCHER_H


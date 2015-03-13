#include "hext/NodeUtil.h"


namespace hext {


unsigned int GetNodePositionWithinParent(const GumboNode * node)
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

std::string GetNodeText(const GumboNode * node)
{
  return TrimAndCollapseWs(GetNodeRawText(node));
}

std::string GetNodeRawText(const GumboNode * node)
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return "";

  std::string inner_text;

  const GumboVector * children = &node->v.element.children;
  for(unsigned int i = 0; i < children->length; ++i)
  {
    const GumboNode * child_node =
      static_cast<const GumboNode *>(children->data[i]);
    assert(child_node != nullptr);

    if( child_node->type == GUMBO_NODE_TEXT )
    {
      const GumboText * node_text = &child_node->v.text;
      assert(node_text != nullptr);
      assert(node_text->text != nullptr);
      inner_text.push_back(' ');
      inner_text.append(node_text->text);
    }
    else if( child_node->type == GUMBO_NODE_ELEMENT )
    {
      inner_text.push_back(' ');
      inner_text.append(GetNodeRawText(child_node));
    }
  }

  return inner_text;
}

std::string GetNodeInnerHtml(const GumboNode * node)
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return "";

  const GumboStringPiece& b = node->v.element.original_tag;
  const GumboStringPiece& e = node->v.element.original_end_tag;

  if( b.data && b.length > 0 &&
      e.data && e.length > 0 &&
      ( b.data + b.length ) < e.data )
  {
    const char * inner_begin = b.data + b.length;
    std::ptrdiff_t length = std::distance(inner_begin, e.data);
    return std::string(inner_begin, length);
  }

  return "";
}


} // hext


#include "hext/NodeUtil.h"


namespace hext {


unsigned int GetNodePositionWithinParent(
  const GumboNode * node,
  GumboTag count_tag
)
{
  if( !node )
    return 0;

  const GumboNode * parent = node->parent;
  if( !parent || parent->type != GUMBO_NODE_ELEMENT )
    return 0;

  unsigned int pos = 0;
  const GumboVector& child_nodes = parent->v.element.children;
  assert(node->index_within_parent < child_nodes.length);
  // We only have to traverse up to node->index_within_parent, and not the
  // whole GumboVector. node->index_within_parent includes text nodes.
  for(unsigned int i = 0; i <= node->index_within_parent; ++i)
  {
    assert(i < child_nodes.length);
    auto child = static_cast<const GumboNode *>(child_nodes.data[i]);

    if( child && child->type == GUMBO_NODE_ELEMENT )
      if( count_tag == GUMBO_TAG_UNKNOWN || child->v.element.tag == count_tag )
        ++pos;

    if( node == child )
      return pos;
  }

  return 0;
}

unsigned int GetNodePositionWithinParentReverse(
  const GumboNode * node,
  GumboTag count_tag
)
{
  if( !node )
    return 0;

  const GumboNode * parent = node->parent;
  if( !parent || parent->type != GUMBO_NODE_ELEMENT )
    return 0;

  const GumboVector& child_nodes = parent->v.element.children;
  if( !child_nodes.length )
    return 0;

  assert(node->index_within_parent < child_nodes.length);
  unsigned int pos = 0;
  // We only have to traverse down to node->index_within_parent, and not the
  // whole GumboVector. node->index_within_parent includes text nodes.
  for(unsigned int i = child_nodes.length; i-- > node->index_within_parent; )
  {
    assert(i < child_nodes.length);
    auto child = static_cast<const GumboNode *>(child_nodes.data[i]);

    assert(child != nullptr);
    if( child && child->type == GUMBO_NODE_ELEMENT )
      if( count_tag == GUMBO_TAG_UNKNOWN || child->v.element.tag == count_tag )
        ++pos;

    if( node == child )
      return pos;
  }

  return 0;
}

unsigned int GetNodeAttributeCount(const GumboNode * node)
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return 0;

  const GumboVector& attributes = node->v.element.attributes;
  return attributes.length;
}

unsigned int GetNodeChildCount(const GumboNode * node)
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return 0;

  unsigned int count = 0;
  const GumboVector& children = node->v.element.children;
  for(unsigned int i = 0; i < children.length; ++i)
  {
    auto child = static_cast<const GumboNode *>(children.data[i]);
    if( child->type == GUMBO_NODE_ELEMENT )
      count++;
  }

  return count;
}

std::string GetNodeText(const GumboNode * node)
{
  return TrimAndCollapseWs(GetNodeRawText(node));
}

std::string GetNodeRawText(const GumboNode * node)
{
  if( !node )
    return "";

  std::string inner_text;
  if( node->type == GUMBO_NODE_ELEMENT )
  {
    const GumboVector * children = &node->v.element.children;
    for(unsigned int i = 0; i < children->length; ++i)
    {
      auto child_node = static_cast<const GumboNode *>(children->data[i]);
      assert(child_node != nullptr);

      if( child_node->type == GUMBO_NODE_ELEMENT )
      {
        bool requires_spaces = RequiresSpaces(child_node->v.element.tag);

        if( requires_spaces )
          inner_text.push_back(' ');

        inner_text.append(GetNodeRawText(child_node));

        if( requires_spaces )
          inner_text.push_back(' ');
      }
      else
      {
        inner_text.append(GetNodeRawText(child_node));
      }
    }
  }
  else if( node->type == GUMBO_NODE_TEXT )
  {
    const GumboText& node_text = node->v.text;
    assert(node_text.text);
    inner_text.append(node_text.text);
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

bool RequiresSpaces(GumboTag tag)
{
  switch( tag )
  {
    case GUMBO_TAG_A:
    case GUMBO_TAG_ABBR:
    case GUMBO_TAG_ACRONYM:
    case GUMBO_TAG_B:
    case GUMBO_TAG_BDO:
    case GUMBO_TAG_BIG:
    case GUMBO_TAG_CITE:
    case GUMBO_TAG_CODE:
    case GUMBO_TAG_DEL:
    case GUMBO_TAG_DFN:
    case GUMBO_TAG_EM:
    case GUMBO_TAG_FIELDSET:
    case GUMBO_TAG_FONT:
    case GUMBO_TAG_I:
    case GUMBO_TAG_IMG:
    case GUMBO_TAG_INS:
    case GUMBO_TAG_KBD:
    case GUMBO_TAG_LABEL:
    case GUMBO_TAG_LEGEND:
    case GUMBO_TAG_MAP:
    case GUMBO_TAG_OBJECT:
    case GUMBO_TAG_Q:
    case GUMBO_TAG_S:
    case GUMBO_TAG_SAMP:
    case GUMBO_TAG_SMALL:
    case GUMBO_TAG_SPAN:
    case GUMBO_TAG_STRIKE:
    case GUMBO_TAG_STRONG:
    case GUMBO_TAG_SUB:
    case GUMBO_TAG_SUP:
    case GUMBO_TAG_TT:
    case GUMBO_TAG_U:
    case GUMBO_TAG_VAR:
      return false;
    default:
      return true;
  }

  return true;
}


} // namespace hext


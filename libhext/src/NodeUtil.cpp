#include "NodeUtil.h"


namespace hext {


std::string NodeText(const GumboNode * node)
{
  return TrimAndCollapseWs(StripTags(node, /* smart_wrap: */ true));
}

std::string StripTags(const GumboNode * node, bool smart_wrap)
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
      assert(child_node);

      if( smart_wrap && child_node->type == GUMBO_NODE_ELEMENT )
      {
        bool wrap = TagWrapsText(child_node->v.element.tag);

        if( wrap ) inner_text.push_back('\n');
        inner_text.append(StripTags(child_node, smart_wrap));
        if( wrap ) inner_text.push_back('\n');
      }
      else
      {
        inner_text.append(StripTags(child_node, smart_wrap));
      }
    }
  }
  else if( node->type == GUMBO_NODE_TEXT ||
           node->type == GUMBO_NODE_WHITESPACE )
  {
    const GumboText& node_text = node->v.text;
    assert(node_text.text);
    inner_text.append(node_text.text);
  }

  return inner_text;
}

std::string NodeInnerHtml(const GumboNode * node)
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
    auto length = static_cast<std::string::size_type>(
      std::distance(inner_begin, e.data)
    );
    return std::string(inner_begin, length);
  }

  return "";
}

bool TagWrapsText(GumboTag tag) noexcept
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

  assert(false);
}


} // namespace hext


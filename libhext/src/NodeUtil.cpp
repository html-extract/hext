// Copyright 2015,2016 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "NodeUtil.h"

#include <cassert>
#include <cstddef>
#include <iomanip>
#include <iterator>


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

  std::ostringstream os;
  const GumboVector& children = node->v.element.children;
  for(unsigned int i = 0; i < children.length; ++i)
  {
    auto child_node = static_cast<const GumboNode *>(children.data[i]);
    SerializeNode(*child_node, os);
  }

  return os.str();
}

void SerializeNode(const GumboNode& n, std::ostringstream& os)
{
  switch( n.type )
  {
    case GUMBO_NODE_DOCUMENT:
    {
      if( n.v.document.has_doctype )
        SerializeDocument(n.v.document, os);
      break;
    }
    case GUMBO_NODE_TEMPLATE:
    case GUMBO_NODE_ELEMENT:
    {
      SerializeElement(n.v.element, os);
      break;
    }
    case GUMBO_NODE_CDATA:
    {
      // ignore
      break;
    }
    case GUMBO_NODE_COMMENT:
    {
      os << "<!--" << n.v.text.text << "-->";
      break;
    }
    case GUMBO_NODE_TEXT:
    case GUMBO_NODE_WHITESPACE:
    {
      os << n.v.text.text;
      break;
    }
    default:
      assert(false);
      break;
  }
}

void SerializeDocument(const GumboDocument& d, std::ostringstream& os)
{
  os << "<!DOCTYPE";
  if( d.name ) os << ' ' << d.name;
  if( d.public_identifier ) os << ' ' << d.public_identifier;
  if( d.system_identifier ) os << ' ' << d.system_identifier;
  os << ">\n";
}

void SerializeAttribute(const GumboAttribute& a, std::ostringstream& os)
{
  if( a.name )
  {
    os << ' ';
    switch( a.attr_namespace )
    {
      case GUMBO_ATTR_NAMESPACE_NONE:
        break;
      case GUMBO_ATTR_NAMESPACE_XLINK:
        os << "xlink:";
        break;
      case GUMBO_ATTR_NAMESPACE_XML:
        os << "xml:";
        break;
      case GUMBO_ATTR_NAMESPACE_XMLNS:
        os << "xmlns:";
        break;
      default:
        assert(false);
        break;
    }
    os << a.name;
    if( a.value )
      os << '=' << std::quoted(a.value);
  }
}

void SerializeElement(const GumboElement& e, std::ostringstream& os)
{
  os << '<' << gumbo_normalized_tagname(e.tag);

  const GumboVector& attributes = e.attributes;
  for(unsigned int i = 0; i < attributes.length; ++i)
  {
    auto attribute = static_cast<const GumboAttribute *>(attributes.data[i]);
    SerializeAttribute(*attribute, os);
  }

  if( TagIsSelfClosing(e.tag) )
  {
    os << '>';

    const GumboVector& children = e.children;
    for(unsigned int i = 0; i < children.length; ++i)
    {
      auto child_node = static_cast<const GumboNode *>(children.data[i]);
      SerializeNode(*child_node, os);
    }

    os << "</" << gumbo_normalized_tagname(e.tag) << '>';
  }
  else
  {
    os << "/>";
  }
}

bool TagIsSelfClosing(GumboTag tag) noexcept
{
  switch( tag )
  {
    case GUMBO_TAG_AREA:
    case GUMBO_TAG_BASE:
    case GUMBO_TAG_BR:
    case GUMBO_TAG_COL:
    case GUMBO_TAG_EMBED:
    case GUMBO_TAG_HR:
    case GUMBO_TAG_IMG:
    case GUMBO_TAG_INPUT:
    case GUMBO_TAG_KEYGEN:
    case GUMBO_TAG_LINK:
    case GUMBO_TAG_META:
    case GUMBO_TAG_PARAM:
    case GUMBO_TAG_SOURCE:
    case GUMBO_TAG_TRACK:
    case GUMBO_TAG_WBR:
      return false;
    default:
      return true;
  }

  assert(false);
  return false;
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


const GumboNode * NextNode(const GumboNode * node) noexcept
{
  if( !node || node->parent->type != GUMBO_NODE_ELEMENT )
    return nullptr;

  const GumboNode * parent = node->parent;
  auto next_sibling_index = node->index_within_parent + 1;
  if( next_sibling_index < parent->v.element.children.length )
    return static_cast<const GumboNode *>(
        parent->v.element.children.data[next_sibling_index]);

  return nullptr;
}


} // namespace hext


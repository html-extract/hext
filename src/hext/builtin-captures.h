#ifndef HEXT_BUILTIN_CAPTURES_H
#define HEXT_BUILTIN_CAPTURES_H

#include <cassert>
#include <string>

#include <gumbo.h>


namespace hext {
namespace bc {


std::string capture_inner_text(const GumboNode * node)
{
  assert(node != nullptr);
  assert(node->type == GUMBO_NODE_ELEMENT);

  std::string inner_text("");

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
      inner_text.append(node_text->text);
    }
  }

  return inner_text;
}


} // namespace bc
} // namespace hext


#endif // HEXT_BUILTIN_CAPTURES_H


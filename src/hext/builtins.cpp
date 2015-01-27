#include "hext/builtins.h"


namespace hext {
namespace bi {


builtin_func_ptr get_builtin_by_name(const std::string& builtin_name)
{
  if( builtin_name.compare("text") == 0 )
    return text;

  return nullptr;
}

std::string text(const GumboNode * node)
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


} // namespace bi
} // namespace hext


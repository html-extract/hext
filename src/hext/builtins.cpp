#include "hext/builtins.h"


namespace hext {
namespace bi {


builtin_func_ptr get_builtin_by_name(const std::string& builtin_name)
{
  if( builtin_name.compare("text") == 0 )
    return text;
  else if( builtin_name.compare("raw_text") == 0 )
    return raw_text;

  return nullptr;
}

std::string get_name_by_builtin(builtin_func_ptr f)
{
  if( f == text )
    return "text";
  else if( f == raw_text )
    return "raw_text";

  return "unknown-builtin";
}

std::string text(const GumboNode * node)
{
  std::string str = raw_text(node);
  boost::algorithm::trim(str);
  return str;
}

std::string raw_text(const GumboNode * node)
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


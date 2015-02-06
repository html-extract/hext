#include "hext/builtins.h"


namespace hext {
namespace bi {


builtin_func_ptr get_builtin_by_name(const std::string& builtin_name)
{
  if( builtin_name.compare("text") == 0 )
    return text;

  return nullptr;
}

std::string get_name_by_builtin(builtin_func_ptr f)
{
  if( f == text )
    return "text";

  return "unknown-builtin";
}

std::string text(const GumboNode * node)
{
  return trim_and_collapse_ws(raw_text(node));
}

std::string raw_text(const GumboNode * node)
{
  assert(node != nullptr);
  assert(node->type == GUMBO_NODE_ELEMENT);

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
      inner_text.append(text(child_node));
    }
  }

  return inner_text;
}

std::string trim_and_collapse_ws(std::string str)
{
  std::string::size_type i = 0;
  std::string::size_type c = 0;
  bool need_space = false;

  for(; c < str.size(); c++)
  {
    if( std::isspace(str[c]) )
    {
      if( i > 0 )
        need_space = true;
    }
    else
    {
      if( need_space )
      {
        str[i++] = ' ';
        need_space = false;
      }
      str[i++] = str[c];
    }
  }

  str.erase(i);
  return str;
}


} // namespace bi
} // namespace hext


#include "hext/builtins.h"


namespace hext {
namespace bi {


BuiltinFuncPtr get_builtin_by_name(const std::string& builtin_name)
{
  if( builtin_name.compare("text") == 0 )
    return get_node_text;
  else if( builtin_name.compare("inner_html") == 0 )
    return get_node_inner_html;

  return nullptr;
}

std::string get_name_by_builtin(BuiltinFuncPtr f)
{
  if( f == get_node_text )
    return "text";
  else if( f == get_node_inner_html )
    return "inner_html";

  return "unknown-builtin";
}


} // namespace bi
} // namespace hext


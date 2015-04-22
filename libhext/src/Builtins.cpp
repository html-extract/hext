#include "hext/Builtins.h"


namespace hext {


BuiltinFuncPtr GetBuiltinByName(const std::string& builtin_name)
{
  if( builtin_name.compare("text") == 0 )
    return GetNodeText;
  else if( builtin_name.compare("inner_html") == 0 )
    return GetNodeInnerHtml;
  else if( builtin_name.compare("strip_tags") == 0 )
    return StripTagsWrapper;

  return nullptr;
}

std::string StripTagsWrapper(const GumboNode * node)
{
  return StripTags(node, /* smart_wrap: */ false);
}


} // namespace hext


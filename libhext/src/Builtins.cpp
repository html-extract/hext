#include "hext/Builtins.h"


namespace hext {


std::string StripTagsWrapper(const GumboNode * node)
{
  return StripTags(node, /* smart_wrap: */ false);
}


} // namespace hext


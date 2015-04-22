#include "hext/pattern/TextNodeMatch.h"


namespace hext {


bool TextNodeMatch::matches(const GumboNode * node) const
{
  return ( node && node->type == GUMBO_NODE_TEXT );
}


} // namespace hext


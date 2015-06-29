#ifndef HEXT_PATTERN_TEXT_NODE_MATCH_H_INCLUDED
#define HEXT_PATTERN_TEXT_NODE_MATCH_H_INCLUDED

#include "hext/pattern/MatchPattern.h"

#include <gumbo.h>


namespace hext {


/// A TextNodeMatch is a MatchPattern that matches text nodes.
class TextNodeMatch : public MatchPattern
{
public:
  /// Return true if node is a text node.
  bool matches(const GumboNode * node) const final
    { return ( node && node->type == GUMBO_NODE_TEXT ); }
};


} // namespace hext


#endif // HEXT_PATTERN_TEXT_NODE_MATCH_H_INCLUDED


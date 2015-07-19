#ifndef HEXT_TEXT_NODE_MATCH_H_INCLUDED
#define HEXT_TEXT_NODE_MATCH_H_INCLUDED

/// @file
///   Declares hext::TextNodeMatch

#include "hext/Match.h"

#include <gumbo.h>


namespace hext {


/// Matches if an HTML node is a text node.
class TextNodeMatch : public Match
{
public:
  /// Returns true if node is a text node.
  bool matches(const GumboNode * node) const final;
};


} // namespace hext


#endif // HEXT_TEXT_NODE_MATCH_H_INCLUDED


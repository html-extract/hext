#ifndef HEXT_ATTRIBUTE_COUNT_MATCH_H_INCLUDED
#define HEXT_ATTRIBUTE_COUNT_MATCH_H_INCLUDED

#include "hext/Match.h"

#include <gumbo.h>


namespace hext {


/// Matches nodes that have a certain amount of attributes.
class AttributeCountMatch : public Match
{
public:
  explicit AttributeCountMatch(unsigned int attribute_count);

  /// Return true if node has attribute_count amount of attributes.
  bool matches(const GumboNode * node) const final;

private:
  unsigned int attribute_count_;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_COUNT_MATCH_H_INCLUDED


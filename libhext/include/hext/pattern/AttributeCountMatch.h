#ifndef HEXT_PATTERN_ATTRIBUTE_COUNT_MATCH_H_INCLUDED
#define HEXT_PATTERN_ATTRIBUTE_COUNT_MATCH_H_INCLUDED

#include "hext/pattern/MatchPattern.h"
#include "hext/NodeUtil.h"

#include <gumbo.h>


namespace hext {


/// AttributeCountMatch is a MatchPattern that matches nodes that have a
/// certain amount of attributes.
class AttributeCountMatch : public MatchPattern
{
public:
  /// Construct an AttributeCountMatch that matches nodes with an
  /// attribute_count amount of attributes. If attribute_count is negative,
  /// attribute_count will be set to zero.
  explicit AttributeCountMatch(int attribute_count);

  /// Return true if node has attribute_count amount of attributes.
  bool matches(const GumboNode * node) const final;

private:
  int attribute_count_;
};


} // namespace hext


#endif // HEXT_PATTERN_ATTRIBUTE_COUNT_MATCH_H_INCLUDED


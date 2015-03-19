#ifndef HEXT_PATTERN_ATTRIBUTE_MATCH_H_INCLUDED
#define HEXT_PATTERN_ATTRIBUTE_MATCH_H_INCLUDED

#include "hext/pattern/ValueTest.h"
#include "hext/pattern/ValueMatch.h"

#include <string>
#include <memory>

#include <gumbo.h>


namespace hext {


/// An AttributeMatch is a ValueMatch that checks whether an html-node has
/// any attribute called attr_name which matches value_test.
class AttributeMatch : public ValueMatch
{
public:
  AttributeMatch(
    const std::string& attr_name,
    std::unique_ptr<ValueTest> value_test
  );
  MatchResult matches(const GumboNode * node) const final;

protected:
  const std::string attr_;
};


} // namespace hext


#endif // HEXT_PATTERN_ATTRIBUTE_MATCH_H_INCLUDED


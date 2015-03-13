#ifndef HEXT_PATTERN_ATTRIBUTE_MATCH_H_INCLUDED
#define HEXT_PATTERN_ATTRIBUTE_MATCH_H_INCLUDED

#include "hext/pattern/ValueTest.h"
#include "hext/pattern/MatchPattern.h"

#include <string>
#include <iostream>
#include <memory>

#include <gumbo.h>


namespace hext {


/// An AttributeMatch is a MatchPattern that checks whether an html-node has
/// any attribute called attr_name which matches value_test.
class AttributeMatch : public MatchPattern
{
public:
  AttributeMatch(
    const std::string& attr_name,
    std::unique_ptr<ValueTest> value_test
  );
  MatchResult matches(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

protected:
  const std::string attr_;
};


} // namespace hext


#endif // HEXT_PATTERN_ATTRIBUTE_MATCH_H_INCLUDED


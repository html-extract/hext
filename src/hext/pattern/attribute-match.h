#ifndef HEXT_ATTRIBUTE_MATCH_H
#define HEXT_ATTRIBUTE_MATCH_H

#include <string>
#include <iostream>
#include <memory>

#include <gumbo.h>

#include "hext/pattern/attr-test.h"
#include "hext/pattern/match-pattern.h"


namespace hext {


/// An AttributeMatch is a MatchPattern that checks whether an html-node has
/// any attribute called attr_name.
class AttributeMatch : public MatchPattern
{
public:
  AttributeMatch(
    const std::string& attr_name,
    std::unique_ptr<AttrTest> attribute_test
  );
  MatchResult matches(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

protected:
  const std::string attr_;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_MATCH_H


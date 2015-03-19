#ifndef HEXT_PATTERN_VALUE_MATCH_H_INCLUDED
#define HEXT_PATTERN_VALUE_MATCH_H_INCLUDED

#include "hext/pattern/ValueTest.h"
#include "hext/pattern/MatchPattern.h"

#include <memory>
#include <iostream>

#include <gumbo.h>


namespace hext {


/// A ValueMatch is a MatchPattern that contains a ValueTest. ValueTests are
/// matched against an html-node-attribute's value.
class ValueMatch : public MatchPattern
{
public:
  ValueMatch(std::unique_ptr<ValueTest> value_test);
  virtual MatchResult matches(const GumboNode * node) const = 0;
  virtual void print(std::ostream& out = std::cout) const = 0;

protected:
  const std::unique_ptr<ValueTest> test_;
};


} // namespace hext


#endif // HEXT_PATTERN_VALUE_MATCH_H_INCLUDED


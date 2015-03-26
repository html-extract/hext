#ifndef HEXT_PATTERN_CONTAINS_TEST_H_INCLUDED
#define HEXT_PATTERN_CONTAINS_TEST_H_INCLUDED

#include "hext/pattern/ValueTest.h"

#include <string>


namespace hext {


/// A ContainsTest is a ValueTest that checks whether a string is contained in
/// another string.
class ContainsTest : public ValueTest
{
public:
  explicit ContainsTest(std::string literal);

  /// Return true if subject contains literal.
  bool test(const char * subject) const final;

private:
  const std::string lit_;
};


} // namespace hext


#endif // HEXT_PATTERN_CONTAINS_TEST_H_INCLUDED


#ifndef HEXT_PATTERN_LITERAL_TEST_H_INCLUDED
#define HEXT_PATTERN_LITERAL_TEST_H_INCLUDED

#include <string>
#include <iostream>

#include "hext/pattern/value-test.h"


namespace hext {


/// A LiteralTest is a ValueTest that checks whether another string equals a
/// given string completely.
class LiteralTest : public ValueTest
{
public:
  explicit LiteralTest(std::string literal);
  /// Return true if subject equals literal.
  bool test(const char * subject) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const std::string lit_;
};


} // namespace hext


#endif // HEXT_PATTERN_LITERAL_TEST_H_INCLUDED


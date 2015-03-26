#ifndef HEXT_PATTERN_IS_NOT_LITERAL_TEST_H_INCLUDED
#define HEXT_PATTERN_IS_NOT_LITERAL_TEST_H_INCLUDED

#include "hext/pattern/ValueTest.h"

#include <string>


namespace hext {


/// An IsNotLiteralTest is a ValueTest that checks whether another string does
/// not equal a given literal.
class IsNotLiteralTest : public ValueTest
{
public:
  explicit IsNotLiteralTest(std::string literal);

  /// Return true if subject is not literal.
  bool test(const char * subject) const final;

private:
  const std::string lit_;
};


} // namespace hext


#endif // HEXT_PATTERN_IS_NOT_LITERAL_TEST_H_INCLUDED


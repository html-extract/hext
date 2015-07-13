#ifndef HEXT_CONTAINS_TEST_H_INCLUDED
#define HEXT_CONTAINS_TEST_H_INCLUDED

#include "hext/ValueTest.h"

#include <string>


namespace hext {


/// Test whether a string is contained in another string.
class ContainsTest : public ValueTest
{
public:
  explicit ContainsTest(std::string literal);

  /// Return true if subject contains literal.
  bool test(const char * subject) const final;

private:
  std::string lit_;
};


} // namespace hext


#endif // HEXT_CONTAINS_TEST_H_INCLUDED


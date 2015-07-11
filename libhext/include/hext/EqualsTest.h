#ifndef HEXT_EQUALS_TEST_H_INCLUDED
#define HEXT_EQUALS_TEST_H_INCLUDED

#include "hext/ValueTest.h"

#include <string>


namespace hext {


/// Test whether another string equals a given literal.
class EqualsTest : public ValueTest
{
public:
  explicit EqualsTest(std::string literal);

  /// Return true if subject equals literal.
  bool operator()(const char * subject) const final;

private:
  std::string lit_;
};


} // namespace hext


#endif // HEXT_EQUALS_TEST_H_INCLUDED


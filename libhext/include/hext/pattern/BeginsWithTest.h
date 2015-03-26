#ifndef HEXT_PATTERN_BEGINS_WITH_TEST_H_INCLUDED
#define HEXT_PATTERN_BEGINS_WITH_TEST_H_INCLUDED

#include "hext/pattern/ValueTest.h"

#include <string>
#include <cstring>


namespace hext {


/// A BeginsWithTest is a ValueTest that checks whether another string begins
/// with a given literal.
class BeginsWithTest : public ValueTest
{
public:
  explicit BeginsWithTest(std::string literal);

  /// Return true if subject begins with literal.
  bool test(const char * subject) const final;

private:
  const std::string lit_;
};


} // namespace hext


#endif // HEXT_PATTERN_BEGINS_WITH_TEST_H_INCLUDED


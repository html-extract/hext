#ifndef HEXT_PATTERN_ENDS_WITH_TEST_H_INCLUDED
#define HEXT_PATTERN_ENDS_WITH_TEST_H_INCLUDED

#include "hext/pattern/ValueTest.h"

#include <string>


namespace hext {


/// An EndsWithTest is a ValueTest that checks whether another string ends with
/// a given literal.
class EndsWithTest : public ValueTest
{
public:
  explicit EndsWithTest(std::string literal);

  /// Return true if subject ends with literal.
  bool test(const char * subject) const final;

private:
  const std::string lit_;
};


} // namespace hext


#endif // HEXT_PATTERN_ENDS_WITH_TEST_H_INCLUDED


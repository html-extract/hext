#ifndef HEXT_ENDS_WITH_TEST_H_INCLUDED
#define HEXT_ENDS_WITH_TEST_H_INCLUDED

#include "hext/ValueTest.h"

#include <string>


namespace hext {


/// Test whether another string ends with a given literal.
class EndsWithTest : public ValueTest
{
public:
  explicit EndsWithTest(std::string literal);

  /// Return true if subject ends with literal.
  bool operator()(const char * subject) const final;

private:
  std::string lit_;
};


} // namespace hext


#endif // HEXT_ENDS_WITH_TEST_H_INCLUDED


#ifndef HEXT_BEGINS_WITH_TEST_H_INCLUDED
#define HEXT_BEGINS_WITH_TEST_H_INCLUDED

#include "hext/ValueTest.h"

#include <string>


namespace hext {


/// Test whether a string begins with a given literal.
class BeginsWithTest : public ValueTest
{
public:
  explicit BeginsWithTest(std::string literal);

  /// Return true if subject begins with literal.
  bool operator()(const char * subject) const final;

private:
  std::string lit_;
};


} // namespace hext


#endif // HEXT_BEGINS_WITH_TEST_H_INCLUDED


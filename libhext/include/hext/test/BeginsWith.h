#ifndef HEXT_TEST_BEGINS_WITH_H_INCLUDED
#define HEXT_TEST_BEGINS_WITH_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <string>


namespace hext {
namespace test {


/// Test whether a string begins with a given literal.
class BeginsWith : public ValueTest
{
public:
  explicit BeginsWith(std::string literal);

  /// Return true if subject begins with literal.
  bool operator()(const char * subject) const final;

private:
  std::string lit_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_BEGINS_WITH_H_INCLUDED


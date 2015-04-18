#ifndef HEXT_TEST_EQUALS_H_INCLUDED
#define HEXT_TEST_EQUALS_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <string>


namespace hext {
namespace test {


/// Equals is a ValueTest that checks whether another string equals a given
/// literal.
class Equals : public ValueTest
{
public:
  explicit Equals(std::string literal);

  /// Return true if subject equals literal.
  bool test(const char * subject) const final;

private:
  const std::string lit_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_EQUALS_H_INCLUDED


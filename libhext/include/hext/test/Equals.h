#ifndef HEXT_TEST_EQUALS_H_INCLUDED
#define HEXT_TEST_EQUALS_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <string>


namespace hext {
namespace test {


/// Check whether another string equals a given literal.
class Equals : public ValueTest
{
public:
  explicit Equals(std::string literal)
  : lit_(std::move(literal))
    {}

  /// Return true if subject equals literal.
  bool operator()(const char * subject) const final
  {
    return subject && this->lit_.compare(subject) == 0;
  }

private:
  std::string lit_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_EQUALS_H_INCLUDED


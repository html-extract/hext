#ifndef HEXT_TEST_IS_NOT_EQUAL_H_INCLUDED
#define HEXT_TEST_IS_NOT_EQUAL_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <string>


namespace hext {
namespace test {


/// IsNotEqual is a ValueTest that checks whether another string does not equal
/// a given literal.
class IsNotEqual : public ValueTest
{
public:
  explicit IsNotEqual(std::string literal);

  /// Return true if subject is not literal.
  bool operator()(const char * subject) const final;
private:
  const std::string lit_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_IS_NOT_EQUAL_H_INCLUDED


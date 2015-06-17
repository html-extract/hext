#ifndef HEXT_TEST_NEGATE_H_INCLUDED
#define HEXT_TEST_NEGATE_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <memory>


namespace hext {
namespace test {


/// Negate is a ValueTest that negates the result of another ValueTest.
class Negate : public ValueTest
{
public:
  explicit Negate(std::unique_ptr<ValueTest>&& value_test);

  bool operator()(const char * subject) const final;

private:
  std::unique_ptr<ValueTest> value_test_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_NEGATE_H_INCLUDED


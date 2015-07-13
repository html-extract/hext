#ifndef HEXT_NEGATE_TEST_H_INCLUDED
#define HEXT_NEGATE_TEST_H_INCLUDED

#include "hext/ValueTest.h"

#include <memory>


namespace hext {


/// Negate the result of another ValueTest.
class NegateTest : public ValueTest
{
public:
  explicit NegateTest(std::unique_ptr<ValueTest>&& value_test);

  /// Return true if value_test fails for subject.
  bool test(const char * subject) const final;

private:
  std::unique_ptr<ValueTest> value_test_;
};


} // namespace hext


#endif // HEXT_NEGATE_TEST_H_INCLUDED


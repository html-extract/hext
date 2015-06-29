#ifndef HEXT_TEST_NEGATE_H_INCLUDED
#define HEXT_TEST_NEGATE_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <memory>


namespace hext {
namespace test {


/// Negate the result of another ValueTest.
class Negate : public ValueTest
{
public:
  explicit Negate(std::unique_ptr<ValueTest>&& value_test)
  : value_test_(std::move(value_test))
    {}

  bool operator()(const char * subject) const final
  {
    if( subject && this->value_test_ )
      return !this->value_test_->operator()(subject);

    return true;
  }

private:
  std::unique_ptr<ValueTest> value_test_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_NEGATE_H_INCLUDED


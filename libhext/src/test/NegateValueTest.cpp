#include "hext/test/NegateValueTest.h"


namespace hext {
namespace test {


NegateValueTest::NegateValueTest(std::unique_ptr<ValueTest>&& value_test)
: value_test_(std::move(value_test))
{
}

bool NegateValueTest::operator()(const char * subject) const
{
  if( subject && this->value_test_ )
    return !this->value_test_->operator()(subject);

  return true;
}


} // namespace test
} // namespace hext


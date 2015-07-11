#include "hext/NegateTest.h"

#include <utility>


namespace hext {


NegateTest::NegateTest(std::unique_ptr<ValueTest>&& value_test)
: value_test_(std::move(value_test))
{
}

bool NegateTest::operator()(const char * subject) const
{
  if( this->value_test_ )
    return !this->value_test_->operator()(subject);
  else
    return subject == nullptr;
}


} // namespace hext


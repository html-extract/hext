#include "hext/test/Negate.h"

#include <utility>


namespace hext {
namespace test {


Negate::Negate(std::unique_ptr<ValueTest>&& value_test)
: value_test_(std::move(value_test))
{
}

bool Negate::operator()(const char * subject) const
{
  if( this->value_test_ )
    return !this->value_test_->operator()(subject);
  else
    return subject == nullptr;
}


} // namespace test
} // namespace hext


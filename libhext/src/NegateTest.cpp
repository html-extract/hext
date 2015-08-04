#include "hext/NegateTest.h"

#include <algorithm>
#include <utility>


namespace hext {


NegateTest::NegateTest(std::unique_ptr<ValueTest> value_test) noexcept
: value_test_(std::move(value_test))  // noexcept
{
}

NegateTest::~NegateTest() = default;
NegateTest::NegateTest(NegateTest&& other) = default;

NegateTest::NegateTest(const NegateTest& other)
: value_test_(other.value_test_ ? other.value_test_->clone() : nullptr)
{
}

NegateTest& NegateTest::operator=(NegateTest&& other) = default;

NegateTest& NegateTest::operator=(const NegateTest& other)
{
  using std::swap;
  NegateTest tmp(other);
  swap(*this, tmp);
  return *this;
}

bool NegateTest::test(const char * subject) const
{
  if( this->value_test_ )
    return !this->value_test_->test(subject);
  else
    return subject == nullptr;
}


} // namespace hext


#include "hext/NegateTest.h"

#include <algorithm>
#include <utility>


namespace hext {


NegateTest::NegateTest(std::unique_ptr<ValueTest> test) noexcept
: test_(std::move(test))  // noexcept
{
}

NegateTest::~NegateTest() = default;
NegateTest::NegateTest(NegateTest&& other) = default;

NegateTest::NegateTest(const NegateTest& other)
: test_(other.test_ ? other.test_->clone() : nullptr)
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
  if( this->test_ )
    return !this->test_->test(subject);
  else
    return subject == nullptr;
}


} // namespace hext


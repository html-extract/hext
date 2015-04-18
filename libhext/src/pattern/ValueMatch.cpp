#include "hext/pattern/ValueMatch.h"


namespace hext {


ValueMatch::ValueMatch(std::unique_ptr<test::ValueTest> value_test)
: test_(std::move(value_test))
{
}


} // namespace hext


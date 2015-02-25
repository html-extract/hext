#include "hext/pattern/match-pattern.h"


namespace hext {


MatchPattern::MatchPattern(std::unique_ptr<ValueTest> value_test)
: test_(std::move(value_test))
{
}

MatchPattern::~MatchPattern()
{
}


} // namespace hext


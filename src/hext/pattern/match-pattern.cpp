#include "hext/pattern/match-pattern.h"


namespace hext {


MatchPattern::MatchPattern(std::unique_ptr<AttrTest> attribute_test)
: test(std::move(attribute_test))
{
}

MatchPattern::~MatchPattern()
{
}


} // namespace hext


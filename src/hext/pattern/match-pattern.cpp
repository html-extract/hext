#include "hext/pattern/match-pattern.h"


namespace hext {


MatchPattern::MatchPattern(std::unique_ptr<AttrTest> attribute_test)
: test_(std::move(attribute_test))
{
}

MatchPattern::~MatchPattern()
{
}


} // namespace hext


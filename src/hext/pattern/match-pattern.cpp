#include "hext/pattern/match-pattern.h"


namespace hext {


match_pattern::match_pattern(std::unique_ptr<attr_test> attribute_test)
: test(std::move(attribute_test))
{
}

match_pattern::~match_pattern()
{
}


} // namespace hext


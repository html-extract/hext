#include "hext/PatternValues.h"


namespace hext {


PatternValues::PatternValues()
: nth(0, 0)
, builtin(nullptr)
, optional(false)
, attr_name()
, literal_value()
, cap_var()
, regex_flag(boost::regex::perl)
, regex()
, test(nullptr)
{
}

void PatternValues::reset()
{
  this->builtin = nullptr;
  this->optional = false;
  this->attr_name = "";
  this->literal_value = "";
  this->cap_var = "";
  this->regex_flag = boost::regex::perl;
  this->nth = {0, 0};
  assert(this->test.get() == nullptr);
  this->test = nullptr;
}


} // namespace hext


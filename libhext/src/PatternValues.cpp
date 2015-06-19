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
, trait(nullptr)
, negate(nullptr)
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
  this->regex = boost::optional<boost::regex>();
  this->nth = {0, 0};
  assert(this->test.get() == nullptr);
  this->test = nullptr;
  assert(this->trait.get() == nullptr);
  this->trait = nullptr;
  assert(this->negate.get() == nullptr);
  this->negate = nullptr;
}


} // namespace hext


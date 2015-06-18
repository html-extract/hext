#include "hext/PatternBuilder.h"


namespace hext {


PatternBuilder::PatternBuilder()
: nth(0, 0)
, builtin(nullptr)
, optional(false)
, attr_name()
, literal_value()
, cap_var()
, regex_flag(boost::regex::perl)
, regex()
, test(nullptr)
, mp_()
, cp_()
{
}

std::vector<std::unique_ptr<MatchPattern>>
PatternBuilder::take_match_patterns()
{
  std::vector<std::unique_ptr<MatchPattern>> vec = std::move(this->mp_);

  this->reset();
  this->mp_.clear();

  return std::move(vec);
}

std::vector<std::unique_ptr<CapturePattern>>
PatternBuilder::take_capture_patterns()
{
  std::vector<std::unique_ptr<CapturePattern>> vec = std::move(this->cp_);

  this->reset();
  this->cp_.clear();

  return std::move(vec);
}

void PatternBuilder::reset()
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


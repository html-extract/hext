#include "hext/Hext.h"


namespace hext {


Hext::Hext(const std::string& hext, Option flags)
: rules_()
, flags_(flags)
{
  Parser p(hext.c_str(), hext.c_str() + hext.size());
  this->rules_ = p.parse(this->flags_);
}

Result Hext::extract(const std::string& html) const
{
  Result result;
  Html h(html.c_str(), html.c_str() + html.size());

  for(const auto& rule : this->rules_)
  {
    Result res = h.extract(rule, this->flags_);
    result.insert(result.end(), res.begin(), res.end());
  }

  return result;
}


} // namespace hext


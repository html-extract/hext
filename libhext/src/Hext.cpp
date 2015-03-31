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
    ResultTree rt = h.extract(rule);

    if( !(this->flags_ & Option::KeepInvalid) )
      rt.remove_incomplete_branches();

    hext::Result sub_result = rt.to_result();
    result.insert(result.end(), sub_result.begin(), sub_result.end());
  }

  return result;
}


} // namespace hext


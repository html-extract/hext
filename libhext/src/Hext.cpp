#include "hext/Hext.h"


namespace hext {


Hext::Hext(const std::string& hext, Option flags)
: rule_(nullptr)
, flags_(flags)
{
  Parser p(hext.c_str(), hext.c_str() + hext.size());
  this->rule_ = std::move(p.parse(this->flags_));
}

Result Hext::extract(const std::string& html) const
{
  return this->extract(Html(html));
}

Result Hext::extract(const Html& html) const
{
  std::unique_ptr<ResultTree> rt = rule.extract(html.root());

  if( this->flags_ & Option::RemoveIncomplete )
    rt.remove_incomplete_branches();

  return rt.to_result();
}


} // namespace hext


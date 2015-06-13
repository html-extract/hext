#include "hext/Hext.h"


namespace hext {


Hext::Hext(const std::string& hext)
: rule_(nullptr)
{
  Parser p(hext.c_str(), hext.c_str() + hext.size());
  this->rule_ = std::move(p.parse());
}

Result Hext::extract(const std::string& html) const
{
  return this->extract(Html(html));
}

Result Hext::extract(const Html& html) const
{
  assert(this->rule_);
  std::unique_ptr<ResultTree> rt = this->rule_->extract(html.root());
  return rt->to_result();
}


} // namespace hext


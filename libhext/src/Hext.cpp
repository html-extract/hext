#include "hext/Hext.h"


namespace hext {


Hext::Hext(const std::string& hext)
: rule_(nullptr)
{
  Parser p(hext.c_str(), hext.c_str() + hext.size());
  this->rule_ = std::move(p.parse());
}

std::unique_ptr<ResultTree> Hext::extract(const std::string& html) const
{
  return std::move(this->extract(Html(html)));
}

std::unique_ptr<ResultTree> Hext::extract(const Html& html) const
{
  assert(this->rule_);
  return std::move(this->rule_->extract(html.root()));
}


} // namespace hext


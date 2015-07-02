#include "hext/Hext.h"
#include "hext/Parser.h"
#include "hext/Rule.h"

#include <utility>


namespace hext {


struct Hext::Impl
{
  Impl()
  : top_rule_()
  {
  }

  Impl(Impl&&) = default;
  Impl& operator=(Impl&&) = default;

  Rule top_rule_;
};


Hext::Hext(const std::string& hext)
: impl_(MakeUnique<Hext::Impl>())
{
  Parser p(hext.c_str(), hext.c_str() + hext.size());
  this->impl_->top_rule_ = std::move(p.parse());
}

Hext::Hext(Hext&&) = default;
Hext& Hext::operator=(Hext &&) = default;
Hext::~Hext() = default;

std::unique_ptr<ResultTree> Hext::extract(const std::string& html) const
{
  return std::move(this->extract(Html(html)));
}

std::unique_ptr<ResultTree> Hext::extract(const Html& html) const
{
  return std::move(this->impl_->top_rule_.extract(html.root()));
}


} // namespace hext


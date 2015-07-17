#include "hext/Extractor.h"
#include "hext/Parser.h"
#include "hext/Rule.h"

#include <utility>


namespace hext {


struct Extractor::Impl
{
  Impl()
  : top_rule_()
  {
  }

  Impl(Impl&&) = default;
  Impl& operator=(Impl&&) = default;

  Rule top_rule_;
};


Extractor::Extractor(const std::string& hext)
: impl_(std::make_unique<Extractor::Impl>())
{
  Parser p(hext.c_str(), hext.c_str() + hext.size());
  this->impl_->top_rule_ = std::move(p.parse());
}

Extractor::Extractor(Extractor&&) = default;
Extractor& Extractor::operator=(Extractor &&) = default;
Extractor::~Extractor() = default;

std::unique_ptr<ResultTree> Extractor::extract(const std::string& html) const
{
  return std::move(this->extract(Html(html.c_str(), html.size())));
}

std::unique_ptr<ResultTree> Extractor::extract(const Html& html) const
{
  return std::move(this->impl_->top_rule_.extract(html.root()));
}


} // namespace hext


#include "hext/Extractor.h"

#include "hext/ParseHext.h"

#include <utility>


namespace hext {


Extractor::Extractor(const std::string& hext)
: rule_(std::move(ParseHext(hext.c_str(), hext.size())))
{
}

Extractor::~Extractor() = default;
Extractor::Extractor(Extractor&&) = default;
Extractor& Extractor::operator=(Extractor &&) = default;

std::unique_ptr<ResultTree> Extractor::extract(const std::string& html) const
{
  return std::move(this->extract(Html(html.c_str(), html.size())));
}

std::unique_ptr<ResultTree> Extractor::extract(const Html& html) const
{
  return std::move(this->rule_.extract(html.root()));
}


} // namespace hext


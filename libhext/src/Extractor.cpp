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

hext::Result Extractor::extract(const std::string& html) const
{
  return this->extract(Html(html.c_str(), html.size()));
}

hext::Result Extractor::extract(const Html& html) const
{
  if( this->rule_ )
    return this->rule_->extract(html.root());
  else
    return {};
}


} // namespace hext


#include "hext/hext.h"


namespace hext {


HtmlExtract::HtmlExtract(const std::string& hext)
: rules_()
{
  Parser p(hext.c_str(), hext.c_str() + hext.size());
  this->rules_ = p.parse();
}

Result HtmlExtract::extract(const std::string& html, Option flags) const
{
  Result result;
  Html h(html.c_str(), html.size());

  for(const auto& rule : this->rules_)
  {
    Result res = h.extract(rule, flags);
    result.insert(result.end(), res.begin(), res.end());
  }

  return result;
}


} // namespace hext


#include "hext/Html.h"


namespace hext {


Html::Html(const std::string& html)
: g_outp_(
    gumbo_parse_with_options(
      &kGumboDefaultOptions,
      html.c_str(),
      html.size()
    )
  )
{
}

Html::Html(const char * begin, const char * end)
: g_outp_(
    gumbo_parse_with_options(
      &kGumboDefaultOptions,
      begin,
      std::distance(begin, end)
    )
  )
{
}

Html::~Html()
{
  if( this->g_outp_ )
    gumbo_destroy_output(&kGumboDefaultOptions, this->g_outp_);
}

const GumboNode * Html::root() const
{
  return this->g_outp_ ? this->g_outp_->root : nullptr;
}


} // namespace hext


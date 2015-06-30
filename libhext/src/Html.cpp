#include "hext/Html.h"


namespace hext {


Html::Html(std::string html)
: html_(std::move(html))
, g_outp_(
    gumbo_parse_with_options(
      &kGumboDefaultOptions,
      this->html_.c_str(),
      this->html_.size()
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


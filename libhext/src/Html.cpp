#include "hext/Html.h"


namespace hext {


Html::Html(const char * buffer, std::size_t size)
: g_outp_(
    gumbo_parse_with_options(
      &kGumboDefaultOptions,
      buffer,
      size
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


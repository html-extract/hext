#include "hext/Html.h"

#include <cstring>


namespace hext {


Html::Html(const char * buffer, std::size_t size) noexcept
: g_outp_(
      gumbo_parse_with_options(&kGumboDefaultOptions,
                               buffer,
                               size))  // noexcept
{
}

Html::Html(const char * buffer) noexcept
: g_outp_(
      gumbo_parse_with_options(&kGumboDefaultOptions,
                               buffer,
                               std::strlen(buffer)))  // noexcept
{
}

Html::~Html() noexcept
{
  if( this->g_outp_ )
    gumbo_destroy_output(&kGumboDefaultOptions, this->g_outp_);
}

Html::Html(Html&&) noexcept = default;
Html& Html::operator=(Html&&) noexcept = default;

const GumboNode * Html::root() const noexcept
{
  return this->g_outp_ ? this->g_outp_->root : nullptr;
}


} // namespace hext


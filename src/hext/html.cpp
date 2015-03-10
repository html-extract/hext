#include "hext/html.h"


namespace hext {


Html::Html(const char * buffer, std::size_t length)
: g_outp_(gumbo_parse_with_options(&kGumboDefaultOptions, buffer, length))
{
}

Html::~Html()
{
  if( this->g_outp_ )
    gumbo_destroy_output(&kGumboDefaultOptions, this->g_outp_);
}

ResultTree Html::extract(const Rule& r) const
{
  ResultTree rt(nullptr);
  if( this->g_outp_ )
    r.extract(this->g_outp_->root, &rt);
  return rt;
}


} // namespace hext


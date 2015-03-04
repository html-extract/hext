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

std::unique_ptr<ResultTree> Html::extract(const Rule& r) const
{
  std::unique_ptr<ResultTree> rt = MakeUnique<ResultTree>();
  if( this->g_outp_ )
    r.extract(this->g_outp_->root, rt.get());
  return rt;
}


} // namespace hext


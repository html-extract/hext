#include "hext/html.h"


namespace hext {


Html::Html(const char * buffer, size_t length)
: g_outp(gumbo_parse_with_options(&kGumboDefaultOptions, buffer, length))
{
  if( !this->g_outp )
    throw std::runtime_error("html parsing failed; gumbo_parse returned nullptr");
}

Html::~Html()
{
  assert(this->g_outp != nullptr);
  gumbo_destroy_output(&kGumboDefaultOptions, this->g_outp);
}

std::unique_ptr<MatchTree> Html::extract(const Rule& r) const
{
  assert(this->g_outp != nullptr);
  std::unique_ptr<MatchTree> m = make_unique<MatchTree>();
  r.extract(this->g_outp->root, m.get());
  return m;
}


} // namespace hext


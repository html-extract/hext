#include "hext/matcher.h"


namespace hext {


matcher::matcher(const std::string& path)
: g_outp(nullptr),
  buffer()
{
  {
    std::ifstream file;
    // force exception on error
    file.exceptions(std::ios::failbit | std::ios::badbit);
    file.open(path);

    std::stringstream stream;
    stream << file.rdbuf();

    this->buffer = stream.str();

    file.close();
  }

  this->g_outp = gumbo_parse(this->buffer.c_str());
  if( this->g_outp == nullptr )
    throw std::runtime_error("gumbo_parse returned nullptr");
}

std::unique_ptr<match_tree> matcher::match(const rule& r) const
{
  assert(this->g_outp != nullptr);
  std::unique_ptr<match_tree> m = make_unique<match_tree>();
  r.match_recursively(this->g_outp->root, m.get());
  return m;
}

matcher::~matcher()
{
  assert(this->g_outp != nullptr);
  gumbo_destroy_output(&kGumboDefaultOptions, this->g_outp);
}


} // namespace hext


#ifndef HEXT_HTML_H
#define HEXT_HTML_H

#include <cassert>
#include <string>
#include <stdexcept>
#include <memory>

#include <gumbo.h>

#include "hext/rule.h"
#include "hext/match-tree.h"
#include "hext/make-unique.h"


namespace hext {


class html
{
public:
  html(const char * buffer, size_t length);
  ~html();
  std::unique_ptr<match_tree> extract(const rule& r) const;

private:
  html(const html&) = delete;
  html& operator=(const html&) = delete;

  GumboOutput * g_outp;
};


} // namespace hext


#endif // HEXT_HTML_H


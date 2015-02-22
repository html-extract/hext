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


class Html
{
public:
  Html(const char * buffer, size_t length);
  ~Html();
  std::unique_ptr<MatchTree> extract(const Rule& r) const;

private:
  Html(const Html&) = delete;
  Html& operator=(const Html&) = delete;

  GumboOutput * g_outp;
};


} // namespace hext


#endif // HEXT_HTML_H


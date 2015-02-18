#ifndef HEXT_MATCHER_H
#define HEXT_MATCHER_H

#include <cassert>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>

#include <gumbo.h>

#include "hext/rule.h"
#include "hext/match-tree.h"
#include "hext/make-unique.h"


namespace hext {


class matcher
{
public:
  explicit matcher(const std::string& path);

  std::unique_ptr<match_tree> extract(const rule& r) const;

  ~matcher();

private:
  matcher(const matcher&) = delete;
  matcher& operator=(const matcher&) = delete;

  GumboOutput * g_outp;
  std::string buffer;
};


} // namespace hext


#endif // HEXT_MATCHER_H


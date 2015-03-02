#ifndef HEXT_HTML_H_INCLUDED
#define HEXT_HTML_H_INCLUDED

#include <cassert>
#include <string>
#include <stdexcept>
#include <memory>

#include <gumbo.h>

#include "hext/rule.h"
#include "hext/match-tree.h"
#include "hext/make-unique.h"


namespace hext {


/// Html is a simple RAII wrapper around gumbo.
class Html
{
public:
  /// Parse html at buffer. buffer must live as long as this object.
  Html(const char * buffer, std::size_t length);
  ~Html();

  /// Apply Rule to all nodes and return a MatchTree containing all
  /// captured values.
  std::unique_ptr<MatchTree> extract(const Rule& r) const;

private:
  Html(const Html&) = delete;
  Html& operator=(const Html&) = delete;

  GumboOutput * g_outp_;
};


} // namespace hext


#endif // HEXT_HTML_H_INCLUDED


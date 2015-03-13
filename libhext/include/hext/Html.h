#ifndef HEXT_HTML_H_INCLUDED
#define HEXT_HTML_H_INCLUDED

#include "hext/Rule.h"
#include "hext/Result.h"
#include "hext/Option.h"
#include "hext/ResultTree.h"

#include <gumbo.h>


namespace hext {


/// Html is a simple RAII wrapper around gumbo.
class Html
{
public:
  Html(const char * begin, const char * end);
  ~Html();

  /// Apply Rule to all nodes and return a Result containing all captured
  /// values.
  Result extract(const Rule& r, Option flags = Option::Default) const;

private:
  Html(const Html&) = delete;
  Html& operator=(const Html&) = delete;

  GumboOutput * g_outp_;
};


} // namespace hext


#endif // HEXT_HTML_H_INCLUDED


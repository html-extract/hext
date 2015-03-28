#ifndef HEXT_HTML_H_INCLUDED
#define HEXT_HTML_H_INCLUDED

#include "hext/Rule.h"
#include "hext/ResultTree.h"

#include <gumbo.h>


namespace hext {


/// Html is responsible for parsing html and, given a Rule, extraction of
/// content.
class Html
{
public:
  /// Construct Html. Pointers must be valid until destruction.
  Html(const char * begin, const char * end);
  ~Html();

  /// Apply Rule to all html-nodes and return a ResultTree containing all
  /// captured values.
  ResultTree extract(const Rule& r) const;

private:
  Html(const Html&) = delete;
  Html& operator=(const Html&) = delete;

  GumboOutput * g_outp_;
};


} // namespace hext


#endif // HEXT_HTML_H_INCLUDED


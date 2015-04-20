#ifndef HEXT_HTML_H_INCLUDED
#define HEXT_HTML_H_INCLUDED

#include <string>
#include <iterator>

#include <gumbo.h>


namespace hext {


/// Html is responsible for parsing html.
/// Html is simply a RAII wrapper around gumbo.
class Html
{
public:
  /// Construct Html. String must be valid until destruction.
  explicit Html(const std::string& html);

  /// Construct Html. Pointers must be valid until destruction.
  Html(const char * begin, const char * end);
  ~Html();

  /// Return a handle to the root of the html document.
  const GumboNode * root() const;

private:
  Html(const Html&) = delete;
  Html& operator=(const Html&) = delete;

  /// Gumbo's resource handle.
  GumboOutput * g_outp_;
};


} // namespace hext


#endif // HEXT_HTML_H_INCLUDED


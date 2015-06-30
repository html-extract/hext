#ifndef HEXT_HTML_H_INCLUDED
#define HEXT_HTML_H_INCLUDED

#include <string>

#include <gumbo.h>


namespace hext {


/// Html is responsible for parsing html.
/// Html is simply a RAII wrapper around gumbo.
class Html
{
public:
  explicit Html(std::string html);
  ~Html();

  Html(Html&&) = default;
  Html& operator=(Html&&) = default;

  /// Return a handle to the root of the html document.
  const GumboNode * root() const;

private:
  Html(const Html&) = delete;
  Html& operator=(const Html&) = delete;

  std::string html_;

  /// Gumbo's resource handle.
  GumboOutput * g_outp_;
};


} // namespace hext


#endif // HEXT_HTML_H_INCLUDED


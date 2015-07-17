#ifndef HEXT_HTML_H_INCLUDED
#define HEXT_HTML_H_INCLUDED

#include <cstddef>

#include <gumbo.h>


namespace hext {


/// Html is responsible for parsing html.
/// Html is simply a RAII wrapper around gumbo.
class Html
{
public:
  /// Construct Html from non-owning pointer. Pointer must stay alive until
  /// destruction of this object.
  Html(const char * buffer, std::size_t size);
  ~Html();

  Html(Html&&) = default;
  Html& operator=(Html&&) = default;

  /// Return a handle to the root of the html document.
  /// Pointer is valid as long as this object is alive.
  const GumboNode * root() const;

private:
  Html(const Html&) = delete;
  Html& operator=(const Html&) = delete;

  /// Gumbo's resource handle.
  GumboOutput * g_outp_;
};


} // namespace hext


#endif // HEXT_HTML_H_INCLUDED


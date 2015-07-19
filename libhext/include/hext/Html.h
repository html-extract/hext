#ifndef HEXT_HTML_H_INCLUDED
#define HEXT_HTML_H_INCLUDED

#include <cstddef>

#include <gumbo.h>


namespace hext {


/// A RAII wrapper for Gumbo.
///
/// All HTML is expected to be UTF-8 encoded.
/// Gumbo will parse anything you throw at it. When given invalid or incomplete
/// HTML it will even fix it for you.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   std::string input = "<html>"
///     "<body>This is a string containing html</body>"
///     "</html>";
///   Html page();
///   const GumboNode * root = page.root();
///   // root now points to the top most HTML element (<html>).
///   assert(root);
/// ~~~~~~~~~~~~~
class Html
{
public:
  /// Constructs an Html from a non-owning pointer. The Pointer must stay alive
  /// until the destruction of this instance.
  ///
  /// @param buffer:  A string containing HTML.
  /// @param   size:  The length of the given buffer.
  Html(const char * buffer, std::size_t size);

  ~Html();
  Html(Html&&) = default;
  Html& operator=(Html&&) = default;

  /// Returns a non-owning pointer to the root node of the HTML document.
  /// The pointer is valid until the destruction of this instance.
  const GumboNode * root() const;

private:
  Html(const Html&) = delete;
  Html& operator=(const Html&) = delete;

  /// Gumbo's resource handle.
  GumboOutput * g_outp_;
};


} // namespace hext


#endif // HEXT_HTML_H_INCLUDED


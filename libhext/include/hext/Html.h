// Copyright 2015, 2016 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef HEXT_HTML_H_INCLUDED
#define HEXT_HTML_H_INCLUDED

/// @file
///   Declares hext::Html

#include "hext/Visibility.h"

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
///   Html page("<html><body>This is a string containing html</body></html>");
///   const GumboNode * root = page.root();
///   // root now points to the top most HTML element (<html>).
///   assert(root);
///   Rule html_root(HtmlTag::HTML);
///   assert(html_root.matches(root));
/// ~~~~~~~~~~~~~
class HEXT_PUBLIC Html
{
public:
  /// Constructs an Html from a non-owning null-terminated string.
  ///
  /// @warning  The buffer must stay alive until the destruction of this
  ///           instance.
  ///
  /// @param buffer:  A null-terminated string containing HTML.
  explicit Html(const char * buffer) noexcept;

  /// Constructs an Html from a non-owning pointer.
  ///
  /// @warning  The buffer must stay alive until the destruction of this
  ///           instance.
  ///
  /// @param buffer:  A string containing HTML.
  /// @param   size:  The length of the given buffer.
  Html(const char * buffer, std::size_t size) noexcept;

  ~Html() noexcept;
  Html(Html&&) noexcept = default;
  Html& operator=(Html&&) noexcept = default;

  /// Returns a non-owning pointer to the root node of the HTML document.
  ///
  /// @warning  The pointer may not be used after the destruction of this
  ///           instance.
  const GumboNode * root() const noexcept;

private:
  Html(const Html&) = delete;
  Html& operator=(const Html&) = delete;

  /// Gumbo's resource handle.
  GumboOutput * g_outp_;
};


} // namespace hext


#endif // HEXT_HTML_H_INCLUDED


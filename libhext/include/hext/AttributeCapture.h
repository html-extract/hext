#ifndef HEXT_ATTRIBUTE_CAPTURE_H_INCLUDED
#define HEXT_ATTRIBUTE_CAPTURE_H_INCLUDED

/// @file
///   Declares hext::AttributeCapture

#include "hext/Capture.h"
#include "hext/Cloneable.h"
#include "hext/Result.h"
#include "hext/StringPipe.h"

#include <string>

#include <gumbo.h>
#include <boost/optional.hpp>


namespace hext {


/// Captures an HTML Element's attribute.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * node = ...; // <img src="bob.jpg"/>
///   AttributeCapture img(
///     "src",   // attribute name
///     "image"  // result name
///   );
///   if( auto result = img.capture(node) )
///     // attribute found and captured
///     assert(*result == ResultPair("image", "bob.jpg"));
/// ~~~~~~~~~~~~~
///
/// @par Example with regex:
/// ~~~~~~~~~~~~~~~~~~~~~~~~
///   GumboNode * node = ...; // <a href="/highway-61"></a>
///   AttributeCapture highway(
///     "href",               // attribute name
///     "U.S. Route"          // result name
///     std::make_unique<RegexPipe>(boost::regex("\\d+"))
///   );
///   if( auto result = highway.capture(node) )
///     // attribute found and captured
///     assert(*result == ResultPair("U.S. Route", "61"));
/// ~~~~~~~~~~~~~~~~~~~~~~~~
class AttributeCapture : public Cloneable<AttributeCapture, Capture>
{
public:
  /// Constructs an AttributeCapture.
  ///
  /// @param   attr_name:  The name of the HTML attribute whose value will be
  ///                      captured.
  /// @param result_name:  The name for the result that is returned from
  ///                      AttributeCapture::capture.
  /// @param        pipe:  If given, the captured value will be sent through
  ///                      this StringPipe before returning from capture().
  AttributeCapture(std::string                 attr_name,
                   std::string                 result_name,
                   std::unique_ptr<StringPipe> pipe = nullptr);

  AttributeCapture(const AttributeCapture& other);
  AttributeCapture(AttributeCapture&&) noexcept = default;
  AttributeCapture& operator=(const AttributeCapture& other);
  AttributeCapture& operator=(AttributeCapture&&) noexcept = default;

  /// Captures an HTML element's attribute called attr_name (as given in the
  /// constructor). Optionally applies a StringPipe to the value before
  /// returning.
  ///
  /// @param node:  A pointer to a GumboNode of type GUMBO_NODE_ELEMENT.
  ///
  /// @returns  A pair in the form of {result_name, attribute_value} or
  ///           an empty optional if the attribute cannot be found.
  boost::optional<ResultPair> capture(const GumboNode * node) const final;

private:
  /// The name of the HTML attribute whose value will be captured.
  std::string attr_name_;

  /// The result name of the captured contents, e.g. ResultPair("href", ...).
  std::string name_;

  /// An optional StringPipe that will be applied to the result.
  std::unique_ptr<StringPipe> pipe_;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_CAPTURE_H_INCLUDED


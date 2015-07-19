#ifndef HEXT_ATTRIBUTE_CAPTURE_H_INCLUDED
#define HEXT_ATTRIBUTE_CAPTURE_H_INCLUDED

/// @file
///   Declares hext::AttributeCapture

#include "hext/Capture.h"
#include "hext/Result.h"

#include <string>

#include <gumbo.h>
#include <boost/optional.hpp>
#include <boost/regex.hpp>


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
///     "href",       // attribute name
///     "U.S. Route"  // result name
///     "\d+"         // regex
///   );
///   if( auto result = img.capture(node) )
///     // attribute found and captured
///     assert(*result == ResultPair("U.S. Route", "61"));
/// ~~~~~~~~~~~~~~~~~~~~~~~~
///
/// @anchor RegexBehavior
/// @par Regex behavior:
///   If AttributeCapture was given a regex it will be applied to the captured
///   value. A regex containing a capture group will produce only the matched
///   content of this capture group, otherwise the whole regex match is
///   returned. All capture groups after the first one will be ignored.
///
/// @par Example regex:
///   Input                 | Regex             | Result
///   ----------------------|-------------------|-----------
///   Highway 61 revisited  |  `\d+`            | 61
///   Highway 61 revisited  |  `Highway \d+`    | Highway 61
///   Highway 61 revisited  |  `Highway (\d+)`  | 61
///   Highway 61 revisited  |  `\w+`            | Highway
///   Highway 61 revisited  |  `(\w+) (\d+)`    | Highway
class AttributeCapture : public Capture
{
public:
  /// Constructs an AttributeCapture with an optional regex filter.
  ///
  /// @param   attr_name:  The name of the HTML attribute whose value will be
  ///                      captured.
  /// @param result_name:  The name for the result that is returned from
  ///                      AttributeCapture::capture.
  /// @param       regex:  An optional regular expression that is applied to the
  ///                      captured HTML attribute's value.
  ///                      See @ref RegexBehavior.
  AttributeCapture(
    std::string attr_name,
    std::string result_name,
    boost::optional<boost::regex> regex = {}
  );

  /// Captures an HTML element's attribute called attr_name (as given in the
  /// constructor). Optionally applies a regex to the attribute's value.
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

  /// Optional regex.
  boost::optional<const boost::regex> rx_;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_CAPTURE_H_INCLUDED


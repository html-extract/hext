#ifndef HEXT_FUNCTION_CAPTURE_H_INCLUDED
#define HEXT_FUNCTION_CAPTURE_H_INCLUDED

/// @file
///   Declares hext::FunctionCapture

#include "hext/Result.h"
#include "hext/Capture.h"
#include "hext/CaptureFunction.h"

#include <string>

#include <gumbo.h>
#include <boost/optional.hpp>
#include <boost/regex.hpp>


namespace hext {


/// Captures the result of applying a function to an HTML node.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * node = ...; // <div>5 reasons why foo is better than bar</div>
///   FunctionCapture text(
///     TextBuiltin,  // predefined CaptureFunction
///     "text"        // result name
///   );
///   if( auto result = text.capture(node) )
///     assert(
///       *result == ResultPair("text", "5 reasons why foo is better than bar")
///     );
/// ~~~~~~~~~~~~~
///
/// @par Example with regex:
/// ~~~~~~~~~~~~~~~~~~~~~~~~
///   GumboNode * node = ...; // <div>The result is 25cm.</div>
///   FunctionCapture centimeters(
///     InnerHtmlBuiltin,  // predefined CaptureFunction
///     "centimeters",     // result name
///     boost::regex("(\\d+)cm")
///   );
///   if( auto result = centimeters.capture(node) )
///     assert(*result == ResultPair("centimeters", "25"));
/// ~~~~~~~~~~~~~~~~~~~~~~~~
///
/// @anchor FCRegexBehavior
/// @par Regex behavior:
///   If FunctionCapture was given a regex it will be applied to the captured
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
class FunctionCapture : public Capture
{
public:
  /// Constructs a FunctionCapture.
  ///
  /// @param        func:  The function that will be applied to an HTML node.
  /// @param result_name:  The name for the result that is returned from
  ///                      FuntionCapture::capture.
  /// @param      filter:  An optional regular expression that is applied to
  ///                      the result of the given CaptureFunction.
  ///                      See @ref FCRegexBehavior.
  FunctionCapture(CaptureFunction               func,
                  std::string                   result_name,
                  boost::optional<boost::regex> filter = {});

  /// Captures the result of calling a given CaptureFunction with node as its
  /// argument. Optionally applies a regex to the result.
  ///
  /// @param node:  A pointer to a GumboNode.
  ///
  /// @returns  A pair in the form of {result_name, result_value} or
  ///           an empty optional if the capture failed.
  boost::optional<ResultPair> capture(const GumboNode * node) const final;

private:
  /// The function that will be applied to an HTML node.
  CaptureFunction func_;

  /// The result name of the captured contents, e.g. ResultPair("text", ...).
  std::string name_;

  /// Optional regex.
  boost::optional<const boost::regex> filter_;
};


} // namespace hext


#endif // HEXT_FUNCTION_CAPTURE_H_INCLUDED


#ifndef HEXT_FUNCTION_CAPTURE_H_INCLUDED
#define HEXT_FUNCTION_CAPTURE_H_INCLUDED

/// @file
///   Declares hext::FunctionCapture

#include "hext/Capture.h"
#include "hext/CaptureFunction.h"
#include "hext/Cloneable.h"
#include "hext/Result.h"
#include "hext/StringPipe.h"

#include <string>

#include <gumbo.h>
#include <boost/optional.hpp>


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
///     std::make_unique<RegexPipe>(boost::regex("(\\d+)cm"))
///   );
///   if( auto result = centimeters.capture(node) )
///     assert(*result == ResultPair("centimeters", "25"));
/// ~~~~~~~~~~~~~~~~~~~~~~~~
class FunctionCapture : public Cloneable<FunctionCapture, Capture>
{
public:
  /// Constructs a FunctionCapture.
  ///
  /// @param        func:  The function that will be applied to an HTML node.
  /// @param result_name:  The name for the result that is returned from
  ///                      FuntionCapture::capture.
  /// @param        pipe:  If given, the captured value will be sent through
  ///                      this StringPipe before returning from capture().
  FunctionCapture(CaptureFunction             func,
                  std::string                 result_name,
                  std::unique_ptr<StringPipe> pipe = nullptr);

  FunctionCapture(const FunctionCapture& other);
  FunctionCapture(FunctionCapture&&) noexcept = default;
  FunctionCapture& operator=(const FunctionCapture& other);
  FunctionCapture& operator=(FunctionCapture&&) noexcept = default;

  /// Captures the result of calling a given CaptureFunction with node as its
  /// argument. Optionally applies a StringPipe to the value before returning.
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

  /// An optional StringPipe that will be applied to the result.
  std::unique_ptr<StringPipe> pipe_;
};


} // namespace hext


#endif // HEXT_FUNCTION_CAPTURE_H_INCLUDED


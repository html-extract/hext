#ifndef HEXT_PATTERN_BUILTIN_CAPTURE_H_INCLUDED
#define HEXT_PATTERN_BUILTIN_CAPTURE_H_INCLUDED

#include "hext/Result.h"
#include "hext/pattern/CapturePattern.h"
#include "hext/Builtins.h"

#include <string>

#include <gumbo.h>
#include <boost/optional.hpp>
#include <boost/regex.hpp>


namespace hext {


/// A BuiltinCapture is a CapturePattern that captures the result of applying
/// a builtin function to a node.
class BuiltinCapture : public CapturePattern
{
public:
  /// Construct a BuiltinCapture. See class CapturePattern for an explanation
  /// on how the regex is applied to the result of the builtin function `func`.
  ///
  /// \param result_name
  ///     The name of the capture.
  /// \param func
  ///     A pointer to a builtin function that is applied to a node to obtain
  ///     the captured value.
  /// \param regex
  ///     An optional regular expression that is applied to the result of the
  ///     builtin function `func`.
  BuiltinCapture(
    std::string result_name,
    BuiltinFuncPtr func,
    boost::optional<boost::regex> regex
  );

  /// Return a string pair containing the captured value. First member is
  /// `result_name_`, second member is the result of the builtin function
  /// `func` when applied to `node`. If a regex was given, it will be applied
  /// to the result of the builtin function, capturing only the desired result.
  ResultPair capture(const GumboNode * node) const final;

private:
  /// A pointer to a builtin function that is applied to a node to obtain the
  /// captured value.
  BuiltinFuncPtr func_;
};


} // namespace hext


#endif // HEXT_PATTERN_BUILTIN_CAPTURE_H_INCLUDED


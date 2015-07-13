#ifndef HEXT_FUNCTION_CAPTURE_H_INCLUDED
#define HEXT_FUNCTION_CAPTURE_H_INCLUDED

#include "hext/Result.h"
#include "hext/Capture.h"
#include "hext/CaptureFunction.h"

#include <string>

#include <gumbo.h>
#include <boost/optional.hpp>
#include <boost/regex.hpp>


namespace hext {


/// Capture the result of applying a function to a node.
class FunctionCapture : public Capture
{
public:
  /// Construct a FunctionCapture.
  ///
  /// \param result_name
  ///     The name of the capture.
  /// \param regex
  ///     An optional regular expression that is applied to the result of the
  ///     builtin function `func`.
  FunctionCapture(
    CaptureFunction func,
    std::string result_name,
    boost::optional<boost::regex> regex = {}
  );

  /// Return a string pair containing the captured value. First member is
  /// `result_name_`, second member is the result of the builtin function
  /// `func` when applied to `node`. If a regex was given, it will be applied
  /// to the result of the builtin function, capturing only the desired result.
  boost::optional<ResultPair> capture(const GumboNode * node) const final;

private:
  CaptureFunction func_;

  /// The result name of the captured contents.
  std::string name_;

  /// Optional regex.
  boost::optional<const boost::regex> rx_;
};


} // namespace hext


#endif // HEXT_FUNCTION_CAPTURE_H_INCLUDED


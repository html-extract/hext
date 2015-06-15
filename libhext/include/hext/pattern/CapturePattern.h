#ifndef HEXT_PATTERN_CAPTURE_PATTERN_H_INCLUDED
#define HEXT_PATTERN_CAPTURE_PATTERN_H_INCLUDED

#include "hext/Result.h"

#include <string>
#include <cstring>

#include <boost/regex.hpp>
#include <boost/optional.hpp>
#include <gumbo.h>


namespace hext {


/// CapturePattern is the abstract base class for all patterns that capture
/// values from html-nodes.
///
/// CapturePatterns can have a regex filter, which is applied to the
/// captured value. If the regex contains capture parenthesis only their content
/// is returned, otherwise the whole match. If multiple capture parenthesis are
/// given, only the first one will be used.
/// Examples:
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///   "Highway 61 revisited"  +  regex "(\d+)"           =>  "61"
///   "Highway 61 revisited"  +  regex "Highway \d+"     =>  "Highway 61"
///   "Highway 61 revisited"  +  regex "^([A-Za-z]{2})"  =>  "Hi"
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class CapturePattern
{
public:
  /// Construct a CapturePattern.
  ///
  /// \param result_name
  ///     The name of the capture.
  /// \param regex
  ///     An optional regular expression that is applied to the captured value.
  CapturePattern(
    const std::string& result_name,
    const boost::optional<boost::regex>& regex
  );

  /// Virtual destructor to allow inheriting from CapturePattern.
  virtual ~CapturePattern();

  /// Return a string pair containing the captured value. Implementation is
  /// provided by sub classes.
  virtual ResultPair capture(const GumboNode * node) const = 0;

protected:
  /// Apply regex `rx_` to `str` and return captured contents.
  /// See class CapturePattern for an explanation on how the regex is applied.
  std::string regex_filter(const char * str) const;

  /// The result name of the captured contents.
  const std::string name_;

  /// Optional regex.
  const boost::optional<const boost::regex> rx_;
};


} // namespace hext


#endif // HEXT_PATTERN_CAPTURE_PATTERN_H_INCLUDED


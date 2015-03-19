#ifndef HEXT_PATTERN_CAPTURE_PATTERN_H_INCLUDED
#define HEXT_PATTERN_CAPTURE_PATTERN_H_INCLUDED

#include "hext/ResultTree.h"

#include <string>
#include <cstring>

#include <boost/regex.hpp>
#include <boost/optional.hpp>
#include <gumbo.h>


namespace hext {


/// CapturePattern is the abstract base class for all patterns that are used
/// to capture values from html-nodes. Rules have CapturePatterns.
/// * hext/pattern/attribute-capture.h:
///     <a href={link}
///   From every node that has both html-tag "a" and an attribute called
///   href, extract the contents of the attribute and put it into "link".
///
/// * hext/pattern/builtin-capture.h:
///     <a @text={title}
///   For every node that has html-tag "a", call builtin function "text" and
///   put its return value into "title".
///
/// CapturePatterns may have a regex filter:
///     <a href={product_id/id=(\d+)/}
///   Before saving the value, apply regex "id=(\d+)", producing only what is
///   is specified within the regex's parentheses. If there are no parentheses,
///   the whole value will be returned, effectively discarding the purpose of
///   the regex.
class CapturePattern
{
public:
  explicit CapturePattern(const std::string& result_name);
  CapturePattern(const std::string& result_name, const boost::regex& regex);
  virtual ~CapturePattern();

  /// Return a pair with the result_name and the captured content, which is to
  /// be inserted into a ResultTree.
  virtual ResultTree::NameValuePair capture(const GumboNode * node) const = 0;

protected:
  /// Apply regex rx_ to str and return captured contents.
  /// Returns whole string if regex contains no capture-parentheses.
  std::string regex_filter(const char * str) const;

  /// The result name of the captured contents.
  const std::string name_;

  /// regex is optional
  const boost::optional<const boost::regex> rx_;
};


} // namespace hext


#endif // HEXT_PATTERN_CAPTURE_PATTERN_H_INCLUDED


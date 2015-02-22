#ifndef HEXT_CAPTURE_PATTERN_H
#define HEXT_CAPTURE_PATTERN_H

#include <string>
#include <cstring>
#include <memory>
#include <iostream>

#include <boost/regex.hpp>
#include <gumbo.h>

#include "hext/match-tree.h"
#include "hext/make-unique.h"


namespace hext {


/// CapturePattern is the abstract base class for all patterns that are used
/// to capture values from html-nodes. Rules have CapturePatterns.
/// * hext/pattern/attribute-capture.h:
///     <a href={link}
///   From every node, that has both html-tag "a" and an attribute called
///   href, extract the contents of the attribute and put it into "link".
///
/// * hext/pattern/builtin-capture.h:
///     <a @text={title}
///   For every node, that has html-tag "a", call builtin function "text" and
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
  CapturePattern(const std::string& result_name, const std::string& regex);
  virtual ~CapturePattern();
  /// Return a pair with the result_name and the captured content, which is to
  /// be inserted into a MatchTree.
  virtual MatchTree::NameValuePair capture(const GumboNode * node) const = 0;
  virtual void print(std::ostream& out = std::cout) const = 0;

protected:
  /// Apply regex rx to str and return captured contents.
  /// Returns whole string if regex contains no capture-parentheses.
  std::string regex_filter(const char * str) const;

  /// The result name of the captured contents.
  const std::string name_;
  /// regex is optional; rx is false if no regex was given
  const std::unique_ptr<boost::regex> rx_;
};


} // namespace hext


#endif // HEXT_CAPTURE_PATTERN_H


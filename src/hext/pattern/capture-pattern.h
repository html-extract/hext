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


/// capture_pattern is the abstract base class for all patterns that are used
/// to capture values from html-nodes. Rules have capture_patterns.
/// See also hext/attribute-capture.h and hext/regex-capture.h
class capture_pattern
{
public:
  explicit capture_pattern(const std::string& result_name);
  capture_pattern(const std::string& var_name, const std::string& regex);
  /// Return a pair with the result_name and the captured content, which is to
  /// be inserted into a match_tree.
  virtual match_tree::name_value_pair capture(const GumboNode * node) const = 0;
  virtual void print(std::ostream& out = std::cout) const = 0;
  virtual ~capture_pattern();

protected:
  /// Apply regex rx to str and return captured contents.
  std::string regex_filter(const char * str) const;

  /// The result name of the captured contents.
  const std::string name;
  /// regex is optional; rx is false if no regex was given
  const std::unique_ptr<boost::regex> rx;
};


} // namespace hext


#endif // HEXT_CAPTURE_PATTERN_H


#ifndef HEXT_PATTERN_CAPTURE_PATTERN_H_INCLUDED
#define HEXT_PATTERN_CAPTURE_PATTERN_H_INCLUDED

#include "hext/Result.h"

#include <string>
#include <cstring>

#include <boost/regex.hpp>
#include <boost/optional.hpp>
#include <gumbo.h>


namespace hext {


/// An abstract base class for all patterns that capture values from html-nodes.
class CapturePattern
{
public:
  CapturePattern();
  virtual ~CapturePattern();

  /// Return a string pair containing the captured value, if any. Implementation
  /// is provided by sub classes.
  virtual boost::optional<ResultPair> capture(const GumboNode * node) const = 0;
};


} // namespace hext


#endif // HEXT_PATTERN_CAPTURE_PATTERN_H_INCLUDED


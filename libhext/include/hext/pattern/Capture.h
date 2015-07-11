#ifndef HEXT_PATTERN_CAPTURE_H_INCLUDED
#define HEXT_PATTERN_CAPTURE_H_INCLUDED

#include "hext/Result.h"

#include <boost/optional.hpp>

#include <gumbo.h>


namespace hext {


/// Abstract base for all Captures that can be applied to html-nodes.
class Capture
{
public:
  virtual ~Capture() {}

  /// Return a string pair containing the captured value, if any. Implementation
  /// is provided by sub classes.
  virtual boost::optional<ResultPair> capture(const GumboNode * node) const = 0;
};


} // namespace hext


#endif // HEXT_PATTERN_CAPTURE_H_INCLUDED


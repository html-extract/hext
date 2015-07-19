#ifndef HEXT_CAPTURE_H_INCLUDED
#define HEXT_CAPTURE_H_INCLUDED

/// @file
///   Declares hext::Capture

#include "hext/Result.h"

#include <boost/optional.hpp>

#include <gumbo.h>


namespace hext {


/// Abstract base for every Capture.
///
/// Captures are applied to HTML elements with Capture::capture() which will
/// return either a ResultPair, or an empty optional if there was nothing to
/// capture.
class Capture
{
public:
  /// Allow inheritance.
  virtual ~Capture() {}

  /// Return a name/value pair with the captured contents or an empty optional,
  /// if there was nothing to capture.
  virtual boost::optional<ResultPair> capture(const GumboNode * node) const = 0;
};


} // namespace hext


#endif // HEXT_CAPTURE_H_INCLUDED


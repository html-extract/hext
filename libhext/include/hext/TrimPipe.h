#ifndef HEXT_TRIM_PIPE_H_INCLUDED
#define HEXT_TRIM_PIPE_H_INCLUDED

/// @file
///   Declares hext::TrimPipe

#include "hext/Cloneable.h"
#include "hext/StringPipe.h"

#include <string>


namespace hext {


/// Trims characters from the beginning and end of a string. Trims space by
/// default.
class TrimPipe : public hext::Cloneable<TrimPipe, StringPipe>
{
public:
  /// Constructs a TrimPipe.
  ///
  /// @param  trim_any_of:  Trim any of these characters from beginning or end
  ///                       of the string. Default: Trim spaces.
  explicit TrimPipe(std::string trim_any_of = " ");

  /// Removes all left and right characters that were given in the constructor
  /// from str.
  std::string transform(std::string str) const final;

private:
  std::string trim_any_of_;
};


} // namespace hext


#endif // HEXT_TRIM_PIPE_H_INCLUDED


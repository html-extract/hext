#ifndef HEXT_APPEND_PIPE_H_INCLUDED
#define HEXT_APPEND_PIPE_H_INCLUDED

/// @file
///   Declares hext::AppendPipe

#include "hext/Cloneable.h"
#include "hext/StringPipe.h"

#include <string>


namespace hext {


/// Appends a given string to a string.
class AppendPipe : public hext::Cloneable<AppendPipe, StringPipe>
{
public:
  /// Constructs an AppendPipe.
  ///
  /// @param  suffix:  The string to append.
  explicit AppendPipe(std::string suffix);

  /// Appends a given string to str.
  std::string transform(std::string str) const final;

private:
  std::string suffix_;
};


} // namespace hext


#endif // HEXT_APPEND_PIPE_H_INCLUDED


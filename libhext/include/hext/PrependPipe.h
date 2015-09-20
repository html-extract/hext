#ifndef HEXT_PREPEND_PIPE_H_INCLUDED
#define HEXT_PREPEND_PIPE_H_INCLUDED

/// @file
///   Declares hext::PrependPipe

#include "hext/Cloneable.h"
#include "hext/StringPipe.h"

#include <string>


namespace hext {


/// Prepends a given string to a string.
class PrependPipe : public hext::Cloneable<PrependPipe, StringPipe>
{
public:
  /// Constructs a PrependPipe.
  ///
  /// @param  prefix:  The string to prepend.
  explicit PrependPipe(std::string prefix);

  /// Prepends a given string to str.
  std::string transform(std::string str) const final;

private:
  std::string prefix_;
};


} // namespace hext


#endif // HEXT_PREPEND_PIPE_H_INCLUDED


#ifndef HEXT_CASE_PIPE_H_INCLUDED
#define HEXT_CASE_PIPE_H_INCLUDED

/// @file
///   Declares hext::CasePipe

#include "hext/Cloneable.h"
#include "hext/StringPipe.h"

#include <string>


namespace hext {


/// Change the case of a string. Changes to lower case by default.
class CasePipe : public hext::Cloneable<CasePipe, StringPipe>
{
public:
  /// CasePipe's options.
  enum Option
  {
    ToLower = 1 << 1,
    ToUpper = 1 << 2
  };

  /// Constructs a CasePipe.
  ///
  /// @param option:  Change the string to this case. Default: to lower case.
  explicit CasePipe(Option option = Option::ToLower);

  /// Changes the case of str.
  std::string transform(std::string str) const final;

private:
  Option option_;
};


} // namespace hext


#endif // HEXT_CASE_PIPE_H_INCLUDED


#ifndef HEXT_REGEX_REPLACE_PIPE_H_INCLUDED
#define HEXT_REGEX_REPLACE_PIPE_H_INCLUDED

/// @file
///   Declares hext::RegexReplacePipe

#include "hext/Cloneable.h"
#include "hext/StringPipe.h"

#include <string>

#include <boost/regex.hpp>


namespace hext {


/// Replaces a string within a string according to a given regex.
///
/// @par Example:
///   Use backreferences to address capture groups:
///   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///     RegexReplacePipe r(boost::regex("^(\\w+) (\\\w+)$"), "$2 $1");
///     r.transform("first second");    // "second first"
///   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class RegexReplacePipe : public hext::Cloneable<RegexReplacePipe, StringPipe>
{
public:
  /// Constructs a RegexReplacePipe.
  ///
  /// @param regex:  A regular expression that is applied to the string.
  /// @param   str:  The string that will replace the portion matching regex.
  RegexReplacePipe(boost::regex regex, std::string str);

  /// Replaces a string within str according to the regex given in the
  /// constructor.
  std::string transform(std::string str) const final;

private:
  boost::regex regex_;
  std::string replace_;
};


} // namespace hext


#endif // HEXT_REGEX_REPLACE_PIPE_H_INCLUDED


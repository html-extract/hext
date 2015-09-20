#ifndef HEXT_REGEX_PIPE_H_INCLUDED
#define HEXT_REGEX_PIPE_H_INCLUDED

/// @file
///   Declares hext::RegexPipe

#include "hext/Cloneable.h"
#include "hext/StringPipe.h"

#include <string>

#include <boost/regex.hpp>


namespace hext {


/// Filters a string according to a given regex.
///
/// @anchor RegexPipeBehavior
/// @par Regex behavior:
///   A regex containing a capture group will produce only the matched
///   content of this capture group, otherwise the whole regex match is
///   returned. All capture groups after the first one will be ignored.
///
/// @par Example regex:
///   Input                 | Regex             | Result
///   ----------------------|-------------------|-----------
///   Highway 61 revisited  |  `\d+`            | 61
///   Highway 61 revisited  |  `Highway \d+`    | Highway 61
///   Highway 61 revisited  |  `Highway (\d+)`  | 61
///   Highway 61 revisited  |  `\w+`            | Highway
///   Highway 61 revisited  |  `(\w+) (\d+)`    | Highway     (not an error)
class RegexPipe : public hext::Cloneable<RegexPipe, StringPipe>
{
public:
  /// Constructs a RegexPipe from a boost::regex.
  ///
  /// @param regex:  A regular expression that is applied to the string.
  ///                See @ref RegexPipeBehavior.
  explicit RegexPipe(boost::regex regex);

  /// Filters the string according to the regex given in the constructor.
  /// See @ref RegexPipeBehavior.
  std::string transform(std::string str) const final;

private:
  boost::regex regex_;
};


} // namespace hext


#endif // HEXT_REGEX_PIPE_H_INCLUDED


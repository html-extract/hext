#ifndef HEXT_HEXT_H_INCLUDED
#define HEXT_HEXT_H_INCLUDED

#include "hext/Parser.h"
#include "hext/Result.h"
#include "hext/Option.h"
#include "hext/Rule.h"
#include "hext/Html.h"

#include <vector>
#include <string>


namespace hext {


/// The class Hext takes a string containing hext rule definitions. Once
/// constructed, the rules can be applied to html by calling Hext::extract,
/// which returns a Result containing all captured values.
class Hext
{
public:
  /// Construct Hext. Throws ParseError if given hext is invalid.
  explicit Hext(const std::string& hext);

  /// Extract values from html. Returns a hext::Result with captured values.
  Result extract(const std::string& html, Option flags = Option::Default) const;

private:
  std::vector<Rule> rules_;
};


} // namespace hext


#endif // HEXT_HEXT_H_INCLUDED


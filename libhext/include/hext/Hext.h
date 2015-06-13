#ifndef HEXT_HEXT_H_INCLUDED
#define HEXT_HEXT_H_INCLUDED

#include "hext/Parser.h"
#include "hext/Result.h"
#include "hext/ResultTree.h"
#include "hext/Rule.h"
#include "hext/Html.h"

#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <algorithm>


/// The hext namespace is the top level namespace for everything in libhext.
namespace hext {


/// Hext takes a string containing hext rule definitions. Once constructed, the
/// rules can be applied to html by calling Hext::extract, which returns a
/// hext::Result containing all captured values.
class Hext
{
public:
  /// Construct Hext. Throws ParseError if given hext is invalid.
  ///
  /// \param hext
  ///     A string containing hext rule definitions.
  explicit Hext(const std::string& hext);

  /// Extract values from a string containing html.
  /// Return a hext::Result containing captured values.
  Result extract(const std::string& html) const;

  /// Extract values from a hext::Html.
  /// Return a hext::Result containing captured values.
  Result extract(const Html& html) const;

private:
  /// Implicit top rule
  std::unique_ptr<Rule> rule_;
};


} // namespace hext


#endif // HEXT_HEXT_H_INCLUDED


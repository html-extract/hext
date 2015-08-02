#ifndef HEXT_EXTRACTOR_H_INCLUDED
#define HEXT_EXTRACTOR_H_INCLUDED

/// @file
///   Declares hext::Extractor

#include "hext/Html.h"
#include "hext/ResultTree.h"
#include "hext/Rule.h"

#include <memory>
#include <string>


/// The hext namespace is the top level namespace for everything in libhext.
namespace hext {


/// Extracts ResultTrees from HTML.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   Extractor ext("<a href={href}/>");
///   auto rt = ext.extract(
///     "<a href='/link'>Link 1</a>"
///     "<a href='/link'>Link 2</a>"
///     "<a href='/link'>Link 3</a>"
///   );
///   auto result = rt->flatten();
///   assert(result.size() == 3);
///   for(const auto& group : result)
///     for(const auto& p : group)
///       assert(p.first == "href" && p.second == "/link")
/// ~~~~~~~~~~~~~
class Extractor
{
public:
  /// Constructs an Extractor with a string containing hext rule definitions.
  /// Throws SyntaxError if given hext is invalid.
  ///
  /// @throws       SyntaxError
  /// @param hext:  A string containing hext rule definitions.
  explicit Extractor(const std::string& hext);

  ~Extractor();
  Extractor(Extractor&&);
  Extractor& operator=(Extractor &&);

  hext::Result extract(const std::string& html) const;

  hext::Result extract(const Html& html) const;

private:
  Extractor(const Extractor&) = delete;
  Extractor& operator=(const Extractor&) = delete;

  std::unique_ptr<Rule> rule_;
};


} // namespace hext


#endif // HEXT_EXTRACTOR_H_INCLUDED


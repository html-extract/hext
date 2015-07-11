#ifndef HEXT_EXTRACTOR_H_INCLUDED
#define HEXT_EXTRACTOR_H_INCLUDED

#include "hext/Html.h"
#include "hext/ResultTree.h"

#include <memory>
#include <string>


/// The hext namespace is the top level namespace for everything in libhext.
namespace hext {


/// Extractor takes a string containing hext rule definitions. Once constructed,
/// the rules can be applied to html by calling Extractor::extract, which
/// returns a hext::ResultTree containing all captured values.
class Extractor
{
public:
  /// Construct Extractor. Throws SyntaxError if given hext is invalid.
  ///
  /// \param hext
  ///     A string containing hext rule definitions.
  explicit Extractor(const std::string& hext);
  Extractor(Extractor&&);
  Extractor& operator=(Extractor &&);
  ~Extractor();

  /// Extract values from a string containing html.
  /// Return a hext::ResultTree containing captured values.
  std::unique_ptr<ResultTree> extract(const std::string& html) const;

  /// Extract values from a hext::Html.
  /// Return a hext::ResultTree containing captured values.
  std::unique_ptr<ResultTree> extract(const Html& html) const;

private:
  Extractor(const Extractor&) = delete;
  Extractor& operator=(const Extractor&) = delete;

  struct Impl;
  std::unique_ptr<Impl> impl_;
};


} // namespace hext


#endif // HEXT_EXTRACTOR_H_INCLUDED


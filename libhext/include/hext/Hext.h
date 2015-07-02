#ifndef HEXT_HEXT_H_INCLUDED
#define HEXT_HEXT_H_INCLUDED

#include "hext/Html.h"
#include "hext/ResultTree.h"
#include "hext/SyntaxError.h"

#include <memory>
#include <string>


/// The hext namespace is the top level namespace for everything in libhext.
namespace hext {


/// Hext takes a string containing hext rule definitions. Once constructed, the
/// rules can be applied to html by calling Hext::extract, which returns a
/// hext::ResultTree containing all captured values.
class Hext
{
public:
  /// Construct Hext. Throws SyntaxError if given hext is invalid.
  ///
  /// \param hext
  ///     A string containing hext rule definitions.
  explicit Hext(const std::string& hext);
  Hext(Hext&&);
  Hext& operator=(Hext &&);
  ~Hext();

  /// Extract values from a string containing html.
  /// Return a hext::ResultTree containing captured values.
  std::unique_ptr<ResultTree> extract(const std::string& html) const;

  /// Extract values from a hext::Html.
  /// Return a hext::ResultTree containing captured values.
  std::unique_ptr<ResultTree> extract(const Html& html) const;

private:
  Hext(const Hext&) = delete;
  Hext& operator=(const Hext&) = delete;

  struct Impl;
  std::unique_ptr<Impl> impl_;
};


} // namespace hext


#endif // HEXT_HEXT_H_INCLUDED


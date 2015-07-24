#ifndef HEXT_FUNCTION_VALUE_MATCH_H_INCLUDED
#define HEXT_FUNCTION_VALUE_MATCH_H_INCLUDED

/// @file
///   Declares hext::FunctionValueMatch

#include "hext/CaptureFunction.h"
#include "hext/Match.h"
#include "hext/ValueTest.h"

#include <memory>

#include <gumbo.h>


namespace hext {


/// Matches if the result of applying a given CaptureFunction to an HTML node
/// passes a ValueTest.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * foo = ...; // <div>This is a foo!</div>
///   GumboNode * bar = ...; // <div>This is a bar!</div>
///
///   FunctionValueMatch m_foo(
///     InnerHtmlBuiltin,                     // CaptureFunction
///     std::unique_ptr<ContainsTest>("foo")  // ValueTest
///   );
///   FunctionValueMatch m_bar(
///     InnerHtmlBuiltin,                     // CaptureFunction
///     std::unique_ptr<ContainsTest>("bar")  // ValueTest
///   );
///
///   assert(m_foo.matches(foo));
///   assert(m_bar.matches(bar));
///
///   assert(!m_foo.matches(bar));
///   assert(!m_bar.matches(foo));
/// ~~~~~~~~~~~~~
class FunctionValueMatch : public Match
{
public:
  /// Constructs a FunctionValueMatch that matches HTML nodes for which a given
  /// CaptureFunction returns a result that passes a ValueTest.
  ///
  /// @param       func:  The CaptureFunction that will be applied to an HTML
  ///                     node.
  /// @param value_test:  The ValueTest that the result of the given
  ///                     CaptureFunction must pass.
  FunctionValueMatch(CaptureFunction            func,
                     std::unique_ptr<ValueTest> value_test);

  /// Returns true if the result of calling the given CaptureFunction with node
  /// as its first argument passes the given ValueTest.
  ///
  /// @param node:  A pointer to a GumboNode.
  bool matches(const GumboNode * node) const final;

private:
  /// The CaptureFunction that will be applied to an HTML node.
  CaptureFunction func_;

  /// The ValueTest that the result of the given CaptureFunction must pass.
  std::unique_ptr<ValueTest> test_;
};


} // namespace hext


#endif // HEXT_FUNCTION_VALUE_MATCH_H_INCLUDED


#ifndef HEXT_FUNCTION_MATCH_H_INCLUDED
#define HEXT_FUNCTION_MATCH_H_INCLUDED

#include "hext/CaptureFunction.h"
#include "hext/Match.h"
#include "hext/ValueTest.h"

#include <memory>

#include <gumbo.h>


namespace hext {


/// Match if the result of applying a function to an html-node passes
/// `value_test`.
class FunctionMatch : public Match
{
public:
  FunctionMatch(
    CaptureFunction func,
    std::unique_ptr<ValueTest> value_test
  );

  /// Return true if the result of applying `func` to node passes `value_test`,
  /// false otherwise.
  bool matches(const GumboNode * node) const final;

private:
  CaptureFunction func_;
  std::unique_ptr<ValueTest> test_;
};


} // namespace hext


#endif // HEXT_FUNCTION_MATCH_H_INCLUDED


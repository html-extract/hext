#ifndef HEXT_PATTERN_VALUE_MATCH_H_INCLUDED
#define HEXT_PATTERN_VALUE_MATCH_H_INCLUDED

#include "hext/pattern/ValueTest.h"
#include "hext/pattern/MatchPattern.h"

#include <memory>

#include <gumbo.h>


namespace hext {


/// A ValueMatch is a MatchPattern that contains a ValueTest.
class ValueMatch : public MatchPattern
{
public:
  /// Construct a ValueMatch.
  ///
  /// \param value_test
  ///     A value_test that is to be applied to a result.
  explicit ValueMatch(std::unique_ptr<ValueTest> value_test);

  /// Implementation must be provided in sub classes.
  virtual MatchResult matches(const GumboNode * node) const = 0;

protected:
  /// The value_test that is to be applied to a result.
  const std::unique_ptr<ValueTest> test_;
};


} // namespace hext


#endif // HEXT_PATTERN_VALUE_MATCH_H_INCLUDED


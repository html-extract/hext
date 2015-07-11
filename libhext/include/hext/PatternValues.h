#ifndef HEXT_PATTERN_VALUES_H_INCLUDED
#define HEXT_PATTERN_VALUES_H_INCLUDED

#include "hext/Builtins.h"
#include "hext/MakeUnique.h"
#include "hext/pattern/Match.h"
#include "hext/pattern/NegateMatch.h"
#include "hext/ValueTest.h"

#include <string>
#include <memory>
#include <utility>

#include <boost/regex.hpp>
#include <boost/optional.hpp>


namespace hext {


/// When parsing hext rule definitions, PatternValues is responsible for holding
/// all values required to create Matches and Captures.
class PatternValues
{
public:
  PatternValues();

  /// Consume generic ValueTest.
  template<typename ValueTestType, typename... Args>
  void set_test(Args&&... arg)
  {
    this->test = MakeUnique<ValueTestType>(std::forward<Args>(arg)...);
  }

  /// Consume generic Trait.
  template<typename MatchType, typename... Args>
  void set_trait(Args&&... arg)
  {
    this->trait = MakeUnique<MatchType>(std::forward<Args>(arg)...);
  }

  /// Reset all members to their original state.
  void reset();

  /// The current nth-pattern for NthChildMatch.
  std::pair<int, int> nth;

  /// The current builtin function.
  BuiltinFuncPtr builtin;

  /// Whether the current Capture is optional.
  bool optional;

  /// The current attribute name.
  std::string attr_name;

  /// The current attribute literal value.
  std::string literal_value;

  /// The current Capture's result name.
  std::string cap_var;

  /// The current regex options.
  boost::regex::flag_type regex_flag;

  /// The current Pattern's regex.
  /// boost::optional is used to be able to distinguish between empty regex
  /// and no regex.
  boost::optional<boost::regex> regex;

  /// The current ValueTest
  std::unique_ptr<ValueTest> test;

  /// The current Trait.
  std::unique_ptr<Match> trait;

  /// The current NegateMatch.
  std::unique_ptr<NegateMatch> negate;
};


} // namespace hext


#endif // HEXT_PATTERN_VALUES_H_INCLUDED


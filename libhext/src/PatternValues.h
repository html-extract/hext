#ifndef HEXT_PATTERN_VALUES_H_INCLUDED
#define HEXT_PATTERN_VALUES_H_INCLUDED

#include "hext/CaptureFunction.h"
#include "hext/Match.h"
#include "hext/NegateMatch.h"
#include "hext/StringPipe.h"
#include "hext/ValueTest.h"

#include <string>
#include <memory>
#include <utility>

#include <boost/regex.hpp>
#include <boost/optional.hpp>


namespace hext {


/// Holds all values required to create every Match and Capture when parsing
/// hext rule definitions.
struct PatternValues
{
  PatternValues();

  /// Consume generic ValueTest.
  template<typename ValueTestType, typename... Args>
  void set_test(Args&&... arg)
  {
    this->test = std::make_unique<ValueTestType>(std::forward<Args>(arg)...);
  }

  /// Consume generic Trait.
  template<typename MatchType, typename... Args>
  void set_trait(Args&&... arg)
  {
    this->trait = std::make_unique<MatchType>(std::forward<Args>(arg)...);
  }

  /// Add generic StringPipe.
  template<typename StringPipeType, typename... Args>
  void add_pipe(Args&&... arg)
  {
    if( this->pipe )
      this->pipe->emplace<StringPipeType>(std::forward<Args>(arg)...);
    else
      this->pipe = std::make_unique<StringPipeType>(std::forward<Args>(arg)...);
  }

  /// Reset all members to their original state.
  void reset();

  /// The current nth-pattern for NthChildMatch.
  std::pair<int, int> nth;

  /// The current builtin function.
  CaptureFunction builtin;

  /// The current attribute name.
  std::string attr_name;

  /// The current attribute literal value.
  std::string literal_value;

  /// The current Capture's result name.
  std::string cap_var;

  /// The current Capture's StringPipe.
  std::unique_ptr<StringPipe> pipe;

  /// The current Match's regex.
  /// boost::optional is used to be able to distinguish between empty regex
  /// and no regex.
  boost::optional<boost::regex> regex;

  /// The current ValueTest.
  std::unique_ptr<ValueTest> test;

  /// The current Trait.
  std::unique_ptr<Match> trait;

  /// The current NegateMatch.
  std::unique_ptr<NegateMatch> negate;

  /// The current regex options.
  boost::regex::flag_type regex_flag;

  /// Whether the current Capture is optional.
  bool optional;
};


} // namespace hext


#endif // HEXT_PATTERN_VALUES_H_INCLUDED


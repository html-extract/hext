#ifndef HEXT_PATTERN_BUILDER_H_INCLUDED
#define HEXT_PATTERN_BUILDER_H_INCLUDED

#include "hext/Builtins.h"
#include "hext/MakeUnique.h"
#include "hext/pattern/AttributeCapture.h"
#include "hext/pattern/AttributeCountMatch.h"
#include "hext/pattern/AttributeMatch.h"
#include "hext/pattern/BuiltinCapture.h"
#include "hext/pattern/BuiltinMatch.h"
#include "hext/pattern/CapturePattern.h"
#include "hext/pattern/ChildCountMatch.h"
#include "hext/pattern/MatchPattern.h"
#include "hext/pattern/NthChildMatch.h"
#include "hext/pattern/TextNodeMatch.h"
#include "hext/test/BeginsWith.h"
#include "hext/test/Contains.h"
#include "hext/test/ContainsWord.h"
#include "hext/test/EndsWith.h"
#include "hext/test/Equals.h"
#include "hext/test/Negate.h"
#include "hext/test/Regex.h"
#include "hext/test/True.h"
#include "hext/test/ValueTest.h"

#include <string>
#include <memory>
#include <utility>
#include <vector>

#include <boost/regex.hpp>
#include <boost/optional.hpp>
#include <gumbo.h>


namespace hext {


/// When parsing hext rule definitions, PatternBuilder is responsible for holding
/// all values required to create MatchPatterns and CapturePatterns.
class PatternBuilder
{
public:
  PatternBuilder();

  /// Move all previously created MatchPatterns to caller.
  std::vector<std::unique_ptr<MatchPattern>> take_match_patterns();

  /// Move all previously created CapturePatterns to caller.
  std::vector<std::unique_ptr<CapturePattern>> take_capture_patterns();

  /// Consume generic MatchPattern.
  template<typename MatchPatternType, typename... Args>
  void push_match(Args&&... arg)
  {
    this->mp_.push_back(
      MakeUnique<MatchPatternType>(std::forward<Args>(arg)...)
    );
  }

  /// Append generic CapturePattern.
  template<typename CapturePatternType, typename... Args>
  void push_capture(Args&&... arg)
  {
    this->cp_.push_back(
      MakeUnique<CapturePatternType>(std::forward<Args>(arg)...)
    );
  }

  /// Consume generic ValueTest.
  template<typename ValueTestType, typename... Args>
  void set_test(Args&&... arg)
  {
    this->test = MakeUnique<ValueTestType>(std::forward<Args>(arg)...);
  }

  /// Reset all public members to their original state.
  void reset();

  /// The current nth-pattern for NthChildMatch.
  std::pair<int, int> nth;

  /// The current builtin function.
  BuiltinFuncPtr builtin;

  /// Whether the current CapturePattern is optional.
  bool optional;

  /// The current attribute name.
  std::string attr_name;

  /// The current attribute literal value.
  std::string literal_value;

  /// The current CapturePattern's result name.
  std::string cap_var;

  /// The current regex options.
  boost::regex::flag_type regex_flag;

  /// The current Pattern's regex.
  /// boost::optional is used to be able to distinguish between empty regex
  /// and no regex.
  boost::optional<boost::regex> regex;

  /// The current ValueTest
  std::unique_ptr<test::ValueTest> test;

private:
  /// Consumed MatchPatterns.
  std::vector<std::unique_ptr<MatchPattern>> mp_;

  /// Consumed CapturePatterns.
  std::vector<std::unique_ptr<CapturePattern>> cp_;
};


} // namespace hext


#endif // HEXT_PATTERN_BUILDER_H_INCLUDED


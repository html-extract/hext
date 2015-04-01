#ifndef HEXT_PATTERN_BUILDER_H_INCLUDED
#define HEXT_PATTERN_BUILDER_H_INCLUDED

#include "hext/Builtins.h"
#include "hext/MakeUnique.h"
#include "hext/Option.h"
#include "hext/pattern/AttributeCapture.h"
#include "hext/pattern/AttributeMatch.h"
#include "hext/pattern/BeginsWithTest.h"
#include "hext/pattern/BuiltinCapture.h"
#include "hext/pattern/BuiltinMatch.h"
#include "hext/pattern/CapturePattern.h"
#include "hext/pattern/ChildCountMatch.h"
#include "hext/pattern/ContainsTest.h"
#include "hext/pattern/ContainsWordTest.h"
#include "hext/pattern/EndsWithTest.h"
#include "hext/pattern/IsNotLiteralTest.h"
#include "hext/pattern/LiteralTest.h"
#include "hext/pattern/MatchPattern.h"
#include "hext/pattern/NthChildMatch.h"
#include "hext/pattern/RegexTest.h"
#include "hext/pattern/ValueTest.h"

#include <string>
#include <memory>
#include <vector>

#include <boost/regex.hpp>
#include <boost/optional.hpp>
#include <gumbo.h>


namespace hext {


/// When parsing hext rule definitions, PatternBuilder is responsible for
/// creating MatchPatterns and CapturePatterns.
class PatternBuilder
{
public:
  PatternBuilder(Option flags_ = DefaultOption);

  /// Consume either a MatchPattern or a CapturePattern, depending on which
  /// parameters were given previously. Reset members.
  void consume_pattern();

  /// Move all previously created MatchPatterns to caller.
  std::vector<std::unique_ptr<MatchPattern>> take_match_patterns();

  /// Move all previously created CapturePatterns to caller.
  std::vector<std::unique_ptr<CapturePattern>> take_capture_patterns();

  /// Consume an NthChildMatch.
  void consume_nth_child(
    NthChildMatch::OffsetOf offset_of = NthChildMatch::OffsetOf::Front,
    GumboTag count_tag = GUMBO_TAG_UNKNOWN
  );

  /// Consume a ChildCountMatch.
  void consume_child_count(const std::string& child_count);

  /// Set builtin function. Return false if builtin cannot be found.
  bool set_builtin(const std::string& bi);

  /// Set attribute name of the Pattern.
  void set_attr_name(const std::string& attribute_name);

  /// Set literal attribute value of the Pattern.
  void set_attr_literal(const std::string& attribute_literal);

  /// Set regex of the Pattern.
  void set_regex(const std::string& regex);

  /// Set the CapturePattern's result name.
  void set_cap_var(const std::string& capture_var);

  /// Set the NthChildMatch's multiplier.
  void set_nth_mul(const std::string& multiplier);

  /// Set the NthChildMatch's addend.
  void set_nth_add(const std::string& addend);

  /// Set literal operator-
  void set_literal_op(char op);

private:
  /// Reset all members to their original state.
  void reset();

  /// Append a MatchPattern.
  void consume_match_pattern();

  /// Append a CapturePattern.
  void consume_capture_pattern();

  /// Options.
  const Option flags_;

  /// The current builtin function.
  BuiltinFuncPtr bf_;

  /// The current attribute name.
  std::string attr_name_;

  /// The current attribute literal value.
  std::string attr_literal_;

  /// The current CapturePattern's result name.
  std::string cap_var_;

  /// The current Pattern's regex.
  /// boost::optional is used to be able to distinguish between empty regex
  /// and no regex.
  boost::optional<boost::regex> regex_;

  /// The current NthChildMatch's multiplier.
  int nth_multiplier_;

  /// The current NthChildMatch's addend.
  int nth_addend_;

  /// The current literal operator.
  char literal_operator_;

  /// Consumed MatchPatterns.
  std::vector<std::unique_ptr<MatchPattern>> mp_;

  /// Consumed CapturePatterns.
  std::vector<std::unique_ptr<CapturePattern>> cp_;
};


} // namespace hext


#endif // HEXT_PATTERN_BUILDER_H_INCLUDED


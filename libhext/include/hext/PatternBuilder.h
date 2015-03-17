#ifndef HEXT_PATTERN_BUILDER_H_INCLUDED
#define HEXT_PATTERN_BUILDER_H_INCLUDED

#include "hext/MakeUnique.h"
#include "hext/Builtins.h"
#include "hext/pattern/ValueTest.h"
#include "hext/pattern/LiteralTest.h"
#include "hext/pattern/RegexTest.h"
#include "hext/pattern/MatchPattern.h"
#include "hext/pattern/CapturePattern.h"
#include "hext/pattern/AttributeMatch.h"
#include "hext/pattern/BuiltinMatch.h"
#include "hext/pattern/AttributeCapture.h"
#include "hext/pattern/BuiltinCapture.h"

#include <string>
#include <memory>
#include <vector>
#include <boost/regex.hpp>
#include <boost/optional.hpp>


namespace hext {


/// When parsing hext rule definitions, a PatternBuilder is responsible for
/// creating MatchPatterns and CapturePatterns.
class PatternBuilder
{
public:
  PatternBuilder();

  /// Consume either a MatchPattern or a CapturePattern, depending on which
  /// parameters were given previously. Reset members.
  void consume_and_reset();

  /// Move all previously created MatchPatterns to caller.
  std::vector<std::unique_ptr<MatchPattern>> get_matchp_and_reset();

  /// Move all previously created CapturePatterns to caller.
  std::vector<std::unique_ptr<CapturePattern>> get_capturep_and_reset();

  bool set_builtin_function(const std::string& bi);
  void set_attr_name(const std::string& attribute_name);
  void set_attr_literal(const std::string& attribute_literal);
  void set_attr_regex(const std::string& attribute_regex);
  void set_cap_var(const std::string& capture_var);
  void set_cap_regex(const std::string& capture_regex);

private:
  /// Reset all members to their original state.
  void reset();

  /// Append a MatchPattern.
  void consume_match_pattern();

  /// Append a CapturePattern.
  void consume_capture_pattern();

  BuiltinFuncPtr bf_;
  std::string attr_name_;
  std::string attr_literal_;
  boost::regex attr_regex_;
  std::string cap_var_;
  boost::optional<boost::regex> cap_regex_;
  std::vector<std::unique_ptr<MatchPattern>> mp_;
  std::vector<std::unique_ptr<CapturePattern>> cp_;
};


} // namespace hext


#endif // HEXT_PATTERN_BUILDER_H_INCLUDED


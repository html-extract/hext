#ifndef HEXT_PATTERN_BUILDER_H_INCLUDED
#define HEXT_PATTERN_BUILDER_H_INCLUDED

#include "hext/make-unique.h"
#include "hext/builtins.h"
#include "hext/pattern/value-test.h"
#include "hext/pattern/literal-test.h"
#include "hext/pattern/regex-test.h"
#include "hext/pattern/match-pattern.h"
#include "hext/pattern/capture-pattern.h"
#include "hext/pattern/attribute-match.h"
#include "hext/pattern/builtin-match.h"
#include "hext/pattern/attribute-capture.h"
#include "hext/pattern/builtin-capture.h"

#include <string>
#include <memory>
#include <boost/regex.hpp>
#include <boost/optional.hpp>


namespace hext {


/// When parsing hext a PatternBuilder is responsible for creating
/// MatchPatterns and CapturePatterns.
class PatternBuilder
{
public:
  PatternBuilder();
  ~PatternBuilder();

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


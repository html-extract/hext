#ifndef HEXT_RULE_BUILDER_H
#define HEXT_RULE_BUILDER_H

#include <string>
#include <memory>
#include <vector>

#include <gumbo.h>

#include "hext/rule.h"
#include "hext/rule-patterns.h"
#include "hext/pattern-builder.h"


namespace hext {


/// When parsing hext a RuleBuilder is responsible for creating Rules.
class RuleBuilder
{
public:
  RuleBuilder();
  ~RuleBuilder();
  /// Return all stored rules and reset.
  std::vector<Rule> get_rules_and_reset();
  /// Reset all members to their original state (except rules_).
  void reset();
  /// Store the Rule that is currently being built and call reset.
  void consume_and_reset();
  /// Store the pattern that is currently being built as a MatchPattern.
  void consume_match_pattern();
  /// Store the pattern that is currently being built as a CapturePattern.
  void consume_capture_pattern();
  PatternBuilder& pattern();

  void reset_indent();
  void increment_indent();
  bool set_tag_name(const std::string& tag);
  void set_optional(bool is_opt);
  void set_nth_child(int pos_within_parent);
  void set_closed(bool closed);

private:
  PatternBuilder pat_;
  std::vector<Rule> rules_;

  unsigned int indent_;
  GumboTag gumbo_tag_;
  bool is_optional_;
  int nth_child_;
  bool is_closed_;
  std::vector<std::unique_ptr<MatchPattern>> mp_;
  std::vector<std::unique_ptr<CapturePattern>> cp_;
};


} // namespace hext


#endif // HEXT_RULE_BUILDER_H


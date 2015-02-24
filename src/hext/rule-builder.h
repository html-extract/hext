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


class RuleBuilder
{
public:
  RuleBuilder();
  ~RuleBuilder();
  std::vector<Rule> get_rules_and_reset();
  void reset();
  void consume_and_reset();
  void consume_match_pattern();
  void consume_capture_pattern();
  PatternBuilder& pattern();

  void reset_indent();
  void increment_indent();
  bool set_tag_name(const std::string& tag);
  void set_optional(bool is_opt);
  void set_direct_descendant(bool direct_desc);
  void set_closed(bool closed);
  void set_nth_child(unsigned int pos_within_parent);

private:
  PatternBuilder pat_;
  std::vector<Rule> rules_;

  unsigned int indent_;
  GumboTag gumbo_tag_;
  bool is_optional_;
  bool is_direct_desc_;
  bool is_closed_;
  unsigned int nth_child_;
  std::vector<std::unique_ptr<MatchPattern>> mp_;
  std::vector<std::unique_ptr<CapturePattern>> cp_;
};


} // namespace hext


#endif // HEXT_RULE_BUILDER_H


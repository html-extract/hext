#ifndef HEXT_RULE_BUILDER_H
#define HEXT_RULE_BUILDER_H


#include <string>
#include <memory>
#include <vector>

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
  void set_tag_name(const std::string& tag);
  void set_optional(bool is_opt);
  void set_direct_descendant(bool direct_desc);
  void set_closed(bool closed);
  void set_nth_child(unsigned int pos_within_parent);

private:
  PatternBuilder pat;
  std::vector<Rule> rules;

  unsigned int indent;
  std::string tag_name;
  bool is_optional;
  bool is_direct_desc;
  bool is_closed;
  unsigned int nth_child;
  std::vector<std::unique_ptr<MatchPattern>> mp;
  std::vector<std::unique_ptr<CapturePattern>> cp;
};


} // namespace hext


#endif // HEXT_RULE_BUILDER_H


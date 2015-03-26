#ifndef HEXT_RULE_BUILDER_H_INCLUDED
#define HEXT_RULE_BUILDER_H_INCLUDED

#include "hext/Rule.h"
#include "hext/Option.h"
#include "hext/RulePatterns.h"
#include "hext/PatternBuilder.h"

#include <string>
#include <memory>
#include <vector>

#include <gumbo.h>


namespace hext {


/// When parsing hext a RuleBuilder is responsible for creating Rules.
class RuleBuilder
{
public:
  explicit RuleBuilder(Option flags);

  /// Return all stored rules and reset.
  std::vector<Rule> get_rules_and_reset();

  /// Reset all members to their original state (except rules_).
  void reset();

  /// Store the Rule that is currently being built and call reset.
  void consume_and_reset();

  PatternBuilder& pattern();
  void reset_indent();
  void increment_indent();
  bool set_tag_name(const std::string& tag_name);
  void set_optional(bool is_optional);
  void set_any_descendant(bool is_any_descendant);
  void set_closed(bool is_closed);
  GumboTag tag() const;

private:
  PatternBuilder pattern_builder_;
  std::vector<Rule> rules_;
  const Option flags_;
  unsigned int indent_;
  GumboTag gumbo_tag_;
  bool is_optional_;
  bool is_any_descendant_;
  bool is_closed_;
};


} // namespace hext


#endif // HEXT_RULE_BUILDER_H_INCLUDED


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
  /// Construct a RuleBuilder.
  explicit RuleBuilder(Option flags);

  /// Move all stored rules to caller.
  std::vector<Rule> take_rules();

  /// Reset to original state.
  void reset();

  /// Store the Rule that is currently being built.
  void consume_rule();

  /// Return a PatternBuilder for this RuleBuilder.
  PatternBuilder& pattern();

  /// Reset the indentation of the current Rule.
  void reset_indent();

  /// Increment indentation of the current Rule by one level.
  void increment_indent();

  /// Set the tag name of the current Rule.
  bool set_tag_name(const std::string& tag_name);

  /// Set the current Rule to optional.
  void set_optional(bool is_optional);

  /// Set the current Rule to any_descendant.
  void set_any_descendant(bool is_any_descendant);

  /// Set the current Rule to path.
  void set_path(bool is_path);

  /// Return the GumboTag of the current Rule.
  GumboTag tag() const;

  /// Return whether the current Rule is a path.
  bool path() const;

private:
  /// The PatternBuilder for this Rule.
  PatternBuilder pattern_builder_;

  /// The previously built Rules.
  std::vector<Rule> rules_;

  /// Options.
  const Option flags_;

  /// The indentation level of the current Rule.
  unsigned int indent_;

  /// The GumboTag of the current Rule.
  GumboTag gumbo_tag_;

  /// Whether the current Rule is optional.
  bool is_optional_;

  /// Whether the current Rule is any_descendant.
  bool is_any_descendant_;

  /// Whether the current Rule is a path.
  bool is_path_;
};


} // namespace hext


#endif // HEXT_RULE_BUILDER_H_INCLUDED


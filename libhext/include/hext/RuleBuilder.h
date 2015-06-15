#ifndef HEXT_RULE_BUILDER_H_INCLUDED
#define HEXT_RULE_BUILDER_H_INCLUDED

#include "hext/Rule.h"
#include "hext/PatternBuilder.h"

#include <memory>
#include <stack>
#include <string>
#include <vector>

#include <boost/optional.hpp>
#include <gumbo.h>


namespace hext {


/// When parsing hext a RuleBuilder is responsible for creating Rules.
class RuleBuilder
{
public:
  /// Construct a RuleBuilder.
  RuleBuilder();

  /// Move stored rule to caller.
  std::unique_ptr<Rule> take_rule();

  /// Reset to original state.
  void reset();

  /// Store the Rule that is currently being built.
  void consume_rule();

  /// Consume and validate a closing tag.
  /// Return false on invalid closing tag.
  bool consume_closing_tag(const std::string& tag_name);

  /// Return the next expected closing tag.
  boost::optional<GumboTag> expected_closing_tag() const;

  /// Return a PatternBuilder for this RuleBuilder.
  PatternBuilder& pattern();

  /// Set the tag name of the current Rule.
  bool set_tag_name(const std::string& tag_name);

  /// Set the current Rule to optional.
  void set_optional(bool is_optional);

  /// Set whether the current Rule is self-closing, e.g. <a href=".." /> is a
  /// self-closing rule.
  void set_self_closing(bool is_self_closing);

  /// Return the GumboTag of the current Rule.
  GumboTag tag() const;

private:
  /// The PatternBuilder for this Rule.
  PatternBuilder pattern_builder_;

  /// The top-most Rule.
  std::unique_ptr<Rule> rule_;

  /// A stack of previously encountered open tags.
  std::stack<GumboTag> tag_stack_;

  /// The GumboTag of the current Rule.
  GumboTag gumbo_tag_;

  /// Whether the current Rule is optional.
  bool is_optional_;

  /// Whether the current Rule is self-closing, e.g. <a href=".." /> is a
  /// self-closing rule.
  bool is_self_closing_;
};


} // namespace hext


#endif // HEXT_RULE_BUILDER_H_INCLUDED


#ifndef HEXT_RULE_BUILDER_H_INCLUDED
#define HEXT_RULE_BUILDER_H_INCLUDED

#include "hext/Rule.h"
#include "hext/HtmlTag.h"

#include <memory>
#include <stack>
#include <string>
#include <vector>

#include <boost/optional.hpp>
#include <gumbo.h>


namespace hext {


/// Stores every Rule when parsing hext.
class RuleBuilder
{
public:
  RuleBuilder();

  /// Moves the current rule to caller.
  Rule take_rule();

  /// Pushes a Rule into the rule tree.
  ///
  /// @param         rule: The rule that is to be appended.
  /// @param self_closing: Whether the given Rule is self-closing, e.g. `<a/>`
  ///                      is a self-closing rule.
  void push_rule(std::unique_ptr<Rule> rule, bool self_closing);

  /// Pushes and validates a closing tag.
  /// Returns false on invalid or unexpected closing tag.
  ///
  /// @param tag_name:  The name of an HTML tag as given by the user.
  bool pop_tag(const std::string& tag_name) noexcept;

  /// Returns the next expected closing tag.
  /// Returns empty if there are no more expected closing tags.
  boost::optional<HtmlTag> get_expected_tag() const;

private:
  /// The current Rule.
  std::unique_ptr<Rule> rule_;

  /// A stack of previously encountered open tags.
  std::stack<HtmlTag> tag_stack_;
};


} // namespace hext


#endif // HEXT_RULE_BUILDER_H_INCLUDED


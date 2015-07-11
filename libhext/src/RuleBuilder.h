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


/// When parsing hext a RuleBuilder is responsible for creating Rules.
class RuleBuilder
{
public:
  RuleBuilder();

  /// Move the current rule tree to caller.
  Rule take_rule_tree();

  /// Push a Rule into the rule tree.
  ///
  /// \param rule:
  ///   The rule. Rules must be moved because they contain std::unique_ptrs.
  ///
  /// \param self_closing:
  ///   Whether the current Rule is self-closing, e.g. `<a/>` is a self-closing
  ///   rule.
  void push_rule(Rule&& rule, bool self_closing);

  /// Push and validate a closing tag.
  /// Return false on invalid or unexpected closing tag.
  bool pop_tag(const std::string& tag_name);

  /// Return the next expected closing tag.
  boost::optional<HtmlTag> get_expected_tag() const;

private:
  /// The current Rules.
  std::vector<Rule> rules_;

  /// A stack of previously encountered open tags.
  std::stack<HtmlTag> tag_stack_;
};


} // namespace hext


#endif // HEXT_RULE_BUILDER_H_INCLUDED


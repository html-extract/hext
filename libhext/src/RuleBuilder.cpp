#include "hext/RuleBuilder.h"


namespace hext {


RuleBuilder::RuleBuilder()
: top_rule_(
    // Implicit top rule that matches everything.
    MakeUnique<Rule>(
      GUMBO_TAG_UNKNOWN,
      false,
      true
    )
  )
, tag_stack_()
{
}

std::unique_ptr<Rule> RuleBuilder::take_rule_tree()
{
  return std::move(this->top_rule_);
}

void RuleBuilder::push_rule(Rule&& rule, bool self_closing)
{
  GumboTag tag = rule.get_tag();

  this->top_rule_->append_child(
    std::move(rule),
    this->tag_stack_.size()
  );

  if( !self_closing )
    this->tag_stack_.push(tag);
}

bool RuleBuilder::pop_tag(const std::string& tag_name)
{
  if( this->tag_stack_.empty() )
    return false;

  GumboTag closing_tag;
  if( tag_name.size() == 1 && tag_name[0] == '*' )
  {
    closing_tag = GUMBO_TAG_UNKNOWN;
  }
  else
  {
    closing_tag = gumbo_tag_enum(tag_name.c_str());
    if( closing_tag == GUMBO_TAG_UNKNOWN )
      return false;
  }

  if( this->tag_stack_.top() == closing_tag )
  {
    this->tag_stack_.pop();
    return true;
  }

  return false;
}

boost::optional<GumboTag> RuleBuilder::get_expected_tag() const
{
  if( this->tag_stack_.empty() )
    return boost::optional<GumboTag>();
  else
    return boost::optional<GumboTag>(this->tag_stack_.top());
}


} // namespace hext


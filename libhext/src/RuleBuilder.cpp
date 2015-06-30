#include "hext/RuleBuilder.h"


namespace hext {


RuleBuilder::RuleBuilder()
: rules_()
, tag_stack_()
{
}

Rule RuleBuilder::take_rule_tree()
{
  assert(this->tag_stack_.empty());
  this->tag_stack_ = std::stack<GumboTag>();

  if( !this->rules_.size() )
    return Rule();

  if( this->rules_.size() == 1 )
  {
    auto rule = std::move(this->rules_.front());
    this->rules_.clear();
    return std::move(rule);
  }

  Rule implicit_top_rule;
  for(auto&& r : this->rules_)
    implicit_top_rule.take_child(std::move(r));
  this->rules_.clear();

  return std::move(implicit_top_rule);
}

void RuleBuilder::push_rule(Rule&& rule, bool self_closing)
{
  GumboTag tag = rule.get_tag();

  std::size_t insert_at_depth = this->tag_stack_.size();
  if( !insert_at_depth )
    this->rules_.push_back(std::move(rule));
  else
    this->rules_.back().take_child(
      std::move(rule),
      insert_at_depth - 1
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


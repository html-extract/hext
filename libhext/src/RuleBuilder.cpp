#include "RuleBuilder.h"


namespace hext {


RuleBuilder::RuleBuilder()
: rule_(nullptr)
, tag_stack_()
{
}

Rule RuleBuilder::take_rule()
{
  assert(this->tag_stack_.empty());
  this->tag_stack_ = std::stack<HtmlTag>();
  if( this->rule_ )
    return std::move(*this->rule_);
  else
    return Rule();
}

void RuleBuilder::push_rule(std::unique_ptr<Rule> rule, bool self_closing)
{
  assert(rule);
  if( !rule )
    return;

  HtmlTag tag = rule->get_tag();

  if( this->rule_ )
  {
    std::size_t insert_at_depth = this->tag_stack_.size();
    this->rule_->append(std::move(*rule), insert_at_depth);
  }
  else
  {
    assert(tag_stack_.empty());
    rule->set_any_descendant(true);
    this->rule_ = std::move(rule);
  }

  if( !self_closing )
    this->tag_stack_.push(tag);
}

bool RuleBuilder::pop_tag(const std::string& tag_name) noexcept
{
  if( this->tag_stack_.empty() )
    return false;

  HtmlTag closing_tag;
  if( tag_name.size() == 1 && tag_name[0] == '*' )
  {
    closing_tag = HtmlTag::ANY;
  }
  else
  {
    GumboTag tag = gumbo_tag_enum(tag_name.c_str());
    if( tag == GUMBO_TAG_UNKNOWN )
      return false;
    closing_tag = static_cast<HtmlTag>(tag);
  }

  if( this->tag_stack_.top() == closing_tag )
  {
    this->tag_stack_.pop();
    return true;
  }

  return false;
}

boost::optional<HtmlTag> RuleBuilder::get_expected_tag() const
{
  if( this->tag_stack_.empty() )
    return {};
  else
    return this->tag_stack_.top();
}


} // namespace hext


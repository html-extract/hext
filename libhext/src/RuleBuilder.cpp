#include "hext/RuleBuilder.h"


namespace hext {


RuleBuilder::RuleBuilder()
: pattern_builder_()
, rule_(
    MakeUnique<Rule>(
      GUMBO_TAG_UNKNOWN,
      false,
      true,
      std::vector<std::unique_ptr<MatchPattern>>(),
      std::vector<std::unique_ptr<CapturePattern>>()
    )
  )
, tag_stack_()
, gumbo_tag_(GUMBO_TAG_UNKNOWN)
, is_optional_(false)
, is_self_closing_(false)
{
}

std::unique_ptr<Rule> RuleBuilder::take_rule()
{
  std::unique_ptr<Rule> r = std::move(this->rule_);

  this->reset();

  return std::move(r);
}

void RuleBuilder::reset()
{
  this->gumbo_tag_ = GUMBO_TAG_UNKNOWN;
  this->is_optional_ = false;
  this->is_self_closing_ = false;
}

void RuleBuilder::consume_rule()
{
  Rule r(
    this->gumbo_tag_,
    this->is_optional_,
    false,
    std::move(this->pattern_builder_.take_match_patterns()),
    std::move(this->pattern_builder_.take_capture_patterns())
  );

  this->rule_->append_child(std::move(r), this->tag_stack_.size());

  if( !this->is_self_closing_ )
    this->tag_stack_.push(this->gumbo_tag_);

  this->reset();
}

bool RuleBuilder::consume_closing_tag(const std::string& tag_name)
{
  if( this->tag_stack_.empty() )
    return false;

  GumboTag closing_tag;
  if( tag_name.empty() )
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

boost::optional<GumboTag> RuleBuilder::expected_closing_tag() const
{
  if( this->tag_stack_.empty() )
    return boost::optional<GumboTag>();
  else
    return boost::optional<GumboTag>(this->tag_stack_.top());
}

PatternBuilder& RuleBuilder::pattern()
{
  return this->pattern_builder_;
}

bool RuleBuilder::set_tag_name(const std::string& tag_name)
{
  if( tag_name.empty() )
  {
    this->gumbo_tag_ = GUMBO_TAG_UNKNOWN;
  }
  else
  {
    GumboTag t = gumbo_tag_enum(tag_name.c_str());
    if( t == GUMBO_TAG_UNKNOWN )
      return false;
    this->gumbo_tag_ = t;
  }

  return true;
}

void RuleBuilder::set_optional(bool is_optional)
{
  this->is_optional_ = is_optional;
}

void RuleBuilder::set_self_closing(bool is_self_closing)
{
  this->is_self_closing_ = is_self_closing;
}

GumboTag RuleBuilder::tag() const
{
  return this->gumbo_tag_;
}


} // namespace hext


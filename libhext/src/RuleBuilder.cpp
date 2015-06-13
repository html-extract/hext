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
, indent_(0)
, gumbo_tag_(GUMBO_TAG_UNKNOWN)
, is_optional_(false)
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
  this->indent_ = 0;
  this->is_optional_ = false;
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

  this->rule_->append_child(std::move(r), this->indent_);
  this->reset();
}

PatternBuilder& RuleBuilder::pattern()
{
  return this->pattern_builder_;
}

void RuleBuilder::reset_indent()
{
  this->indent_ = 0;
}

void RuleBuilder::increment_indent()
{
  this->indent_++;
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

GumboTag RuleBuilder::tag() const
{
  return this->gumbo_tag_;
}


} // namespace hext


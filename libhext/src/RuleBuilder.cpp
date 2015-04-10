#include "hext/RuleBuilder.h"


namespace hext {


RuleBuilder::RuleBuilder(Option flags)
: pattern_builder_(flags)
, rule_(
    MakeUnique<Rule>(
      GUMBO_TAG_UNKNOWN,
      true,
      true,
      true,
      false,
      RulePatterns()
    )
  )
, flags_(flags)
, indent_(0)
, gumbo_tag_(GUMBO_TAG_UNKNOWN)
, is_optional_(false)
, is_any_descendant_(false)
, is_path_(false)
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
  this->is_path_ = false;
  this->is_any_descendant_ = false;
  this->is_optional_ = false;
}

void RuleBuilder::consume_rule()
{
  Rule r(
    this->gumbo_tag_,
    this->is_optional_,
    this->is_any_descendant_,
    this->is_path_,
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

void RuleBuilder::set_any_descendant(bool is_any_descendant)
{
  this->is_any_descendant_ = is_any_descendant;
}

void RuleBuilder::set_path(bool is_path)
{
  this->is_path_ = is_path;
}

GumboTag RuleBuilder::tag() const
{
  return this->gumbo_tag_;
}

bool RuleBuilder::path() const
{
  return this->is_path_;
}


} // namespace hext


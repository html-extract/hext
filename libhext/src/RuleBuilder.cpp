#include "hext/RuleBuilder.h"


namespace hext {


RuleBuilder::RuleBuilder(Option flags)
: pattern_builder_()
, rules_()
, flags_(flags)
, indent_(0)
, gumbo_tag_(GUMBO_TAG_UNKNOWN)
, is_optional_(false)
, is_any_descendant_(false)
, is_closed_(false)
{
}

std::vector<Rule> RuleBuilder::get_rules_and_reset()
{
  std::vector<Rule> rs = std::move(this->rules_);

  this->reset();
  this->rules_.clear();

  return std::move(rs);
}

void RuleBuilder::reset()
{
  this->gumbo_tag_ = GUMBO_TAG_UNKNOWN;
  this->indent_ = 0;
  this->is_closed_ = false;
  this->is_any_descendant_ = false;
  this->is_optional_ = false;
}

void RuleBuilder::consume_and_reset()
{
  Rule r(
    this->gumbo_tag_,
    this->is_optional_,
    (
      this->indent_ == 0 && !(this->flags_ & Option::NoAutoAnyDesc)
      ?
      true : this->is_any_descendant_
    ),
    this->is_closed_,
    RulePatterns(
      std::move(this->pattern_builder_.get_matchp_and_reset()),
      std::move(this->pattern_builder_.get_capturep_and_reset())
    )
  );

  // either top-level rule or first rule
  if( this->indent_ == 0 || this->rules_.empty() )
    this->rules_.push_back(std::move(r));
  else
    this->rules_.back().append_child(std::move(r), this->indent_);

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

void RuleBuilder::set_closed(bool is_closed)
{
  this->is_closed_ = is_closed;
}

GumboTag RuleBuilder::tag() const
{
  return this->gumbo_tag_;
}


} // namespace hext


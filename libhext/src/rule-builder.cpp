#include "hext/rule-builder.h"


namespace hext {


RuleBuilder::RuleBuilder()
: pat_()
, rules_()
, indent_(0)
, gumbo_tag_(GUMBO_TAG_UNKNOWN)
, is_optional_(false)
, nth_child_(-1)
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
  this->nth_child_ = -1;
  this->is_optional_ = false;
}

void RuleBuilder::consume_and_reset()
{
  Rule r(
    this->gumbo_tag_,
    this->is_optional_,
    this->nth_child_,
    this->is_closed_,
    RulePatterns(
      std::move(this->pat_.get_matchp_and_reset()),
      std::move(this->pat_.get_capturep_and_reset())
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
  return this->pat_;
}

void RuleBuilder::reset_indent()
{
  this->indent_ = 0;
}

void RuleBuilder::increment_indent()
{
  this->indent_++;
}

bool RuleBuilder::set_tag_name(const std::string& tag)
{
  if( tag.empty() )
  {
    this->gumbo_tag_ = GUMBO_TAG_UNKNOWN;
  }
  else
  {
    GumboTag t = gumbo_tag_enum(tag.c_str());
    if( t == GUMBO_TAG_UNKNOWN )
      return false;
    this->gumbo_tag_ = t;
  }

  return true;
}

void RuleBuilder::set_optional(bool is_opt)
{
  this->is_optional_ = is_opt;
}

void RuleBuilder::set_nth_child(int pos_within_parent)
{
  if( pos_within_parent < -1 )
    pos_within_parent = -1;
  this->nth_child_ = pos_within_parent;
}

void RuleBuilder::set_closed(bool closed)
{
  this->is_closed_ = closed;
}


} // namespace hext


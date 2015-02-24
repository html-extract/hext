#include "hext/rule-builder.h"


namespace hext {


RuleBuilder::RuleBuilder()
: pat_()
, rules_()
, indent_(0)
, gumbo_tag_(GUMBO_TAG_UNKNOWN)
, is_optional_(false)
, is_direct_desc_(false)
, is_closed_(false)
, nth_child_(0)
, mp_()
, cp_()
{
}

RuleBuilder::~RuleBuilder()
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
  this->is_direct_desc_ = false;
  this->is_closed_ = false;
  this->nth_child_ = 0;
  this->mp_.clear();
  this->cp_.clear();
}

void RuleBuilder::consume_and_reset()
{
  Rule r(
    this->gumbo_tag_,
    this->is_optional_,
    this->is_direct_desc_,
    this->is_closed_,
    this->nth_child_,
    RulePatterns(std::move(this->mp_), std::move(this->cp_))
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
  }

  return true;
}

void RuleBuilder::set_optional(bool is_opt)
{
  this->is_optional_ = is_opt;
}

void RuleBuilder::set_direct_descendant(bool direct_desc)
{
  this->is_direct_desc_ = direct_desc;
}

void RuleBuilder::set_closed(bool closed)
{
  this->is_closed_ = closed;
}

void RuleBuilder::set_nth_child(unsigned int pos_within_parent)
{
  this->nth_child_ = pos_within_parent;
}

void RuleBuilder::consume_match_pattern()
{
  this->mp_.push_back(this->pat_.build_match_and_reset());
}

void RuleBuilder::consume_capture_pattern()
{
  this->cp_.push_back(this->pat_.build_capture_and_reset());
}


} // namespace hext


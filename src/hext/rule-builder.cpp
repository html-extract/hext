#include "hext/rule-builder.h"


namespace hext {


RuleBuilder::RuleBuilder()
: pat()
, rules()
, indent(0)
, tag_name("")
, is_optional(false)
, is_direct_desc(false)
, is_closed(false)
, nth_child(0)
, mp()
, cp()
{
}

RuleBuilder::~RuleBuilder()
{
}

std::vector<Rule> RuleBuilder::get_rules_and_reset()
{
  std::vector<Rule> rs = std::move(this->rules);

  this->reset();
  this->rules.clear();

  return std::move(rs);
}

void RuleBuilder::reset()
{
  this->tag_name = "";
  this->indent = 0;
  this->is_direct_desc = false;
  this->is_closed = false;
  this->nth_child = 0;
  this->mp.clear();
  this->cp.clear();
}

void RuleBuilder::consume_and_reset()
{
  Rule r(
    this->tag_name,
    this->is_optional,
    this->is_direct_desc,
    this->is_closed,
    this->nth_child,
    RulePatterns(std::move(this->mp), std::move(this->cp))
  );

  // either top-level rule or first rule
  if( this->indent == 0 || this->rules.empty() )
    rules.push_back(std::move(r));
  else
    rules.back().append_child(std::move(r), this->indent);

  this->reset();
}

PatternBuilder& RuleBuilder::pattern()
{
  return this->pat;
}

void RuleBuilder::reset_indent()
{
  this->indent = 0;
}

void RuleBuilder::increment_indent()
{
  this->indent++;
}

void RuleBuilder::set_tag_name(const std::string& tag)
{
  this->tag_name = tag;
}

void RuleBuilder::set_optional(bool is_opt)
{
  this->is_optional = is_opt;
}

void RuleBuilder::set_direct_descendant(bool direct_desc)
{
  this->is_direct_desc = direct_desc;
}

void RuleBuilder::set_closed(bool closed)
{
  this->is_closed = closed;
}

void RuleBuilder::set_nth_child(unsigned int pos_within_parent)
{
  this->nth_child = pos_within_parent;
}

void RuleBuilder::consume_match_pattern()
{
  this->mp.push_back(this->pat.build_match_and_reset());
}

void RuleBuilder::consume_capture_pattern()
{
  this->cp.push_back(this->pat.build_capture_and_reset());
}


} // namespace hext


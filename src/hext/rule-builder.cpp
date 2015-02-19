#include "hext/rule-builder.h"


namespace hext {


rule_builder::rule_builder()
: pat()
, tag_name("")
, is_direct_desc(false)
, is_closed(false)
, nth_child(0)
, mp()
, cp()
{
}

rule_builder::~rule_builder()
{
}

rule rule_builder::build_and_reset()
{
  rule r(
    this->tag_name,
    this->is_direct_desc,
    this->is_closed,
    this->nth_child,
    rule_patterns(std::move(this->mp), std::move(this->cp))
  );

  this->tag_name = "";
  this->is_direct_desc = false;
  this->is_closed = false;
  this->nth_child = 0;
  this->mp.clear();
  this->cp.clear();

  return std::move(r);
}

pattern_builder& rule_builder::pattern()
{
  return this->pat;
}

void rule_builder::set_tag_name(const std::string& tag)
{
  this->tag_name = tag;
}

void rule_builder::set_direct_descendant(bool direct_desc)
{
  this->is_direct_desc = direct_desc;
}

void rule_builder::set_closed(bool closed)
{
  this->is_closed = closed;
}

void rule_builder::set_nth_child(unsigned int pos_within_parent)
{
  this->nth_child = pos_within_parent;
}

void rule_builder::consume_match_pattern()
{
  this->mp.push_back(this->pat.build_match_and_reset());
}

void rule_builder::consume_capture_pattern()
{
  this->cp.push_back(this->pat.build_capture_and_reset());
}


} // namespace hext


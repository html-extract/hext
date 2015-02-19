#include "hext/rule-builder.h"


namespace hext {


rule_builder::rule_builder()
: tag_name("")
, is_direct_desc(false)
, is_closed(false)
, nth_child(0)
, mp()
, cp()
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

void rule_builder::append_match_pattern(std::unique_ptr<match_pattern> p)
{
  this->mp.push_back(std::move(p));
}

void rule_builder::append_capture_pattern(std::unique_ptr<capture_pattern> p)
{
  this->cp.push_back(std::move(p));
}


} // namespace hext


#include "hext/rule.h"


namespace hext {


rule::rule()
: children(),
  attributes(),
  tag_name("*"),
  direct_descendant(false),
  capture_limit(1)
{
}

rule::const_child_iterator rule::children_begin() const
{
  return this->children.cbegin();
}

rule::const_child_iterator rule::children_end() const
{
  return this->children.cend();
}

rule::child_iterator rule::children_begin()
{
  return this->children.begin();
}

rule::child_iterator rule::children_end()
{
  return this->children.end();
}

std::vector<rule>::size_type rule::children_size() const
{
  return this->children.size();
}

rule::const_attribute_iterator rule::attributes_begin() const
{
  return this->attributes.cbegin();
}

rule::const_attribute_iterator rule::attributes_end() const
{
  return this->attributes.cend();
}

std::vector<attribute>::size_type rule::attributes_size() const
{
  return this->attributes.size();
}

void rule::append_child(rule r)
{
  this->children.push_back(r);
}

void rule::append_attribute(attribute attr)
{
  this->attributes.push_back(attr);
}

std::string rule::get_tag_name() const
{
  return this->tag_name;
}

bool rule::get_is_direct_descendant() const
{
  return this->direct_descendant;
}

unsigned int rule::get_capture_limit()
{
  return this->capture_limit;
}

void rule::set_tag_name(std::string name)
{
  this->tag_name = name;
}

void rule::set_is_direct_descendant(bool is_direct_descendant)
{
  this->direct_descendant = is_direct_descendant;
}

void rule::set_capture_limit(unsigned int cap_limit)
{
  this->capture_limit = cap_limit;
}


} // namespace hext


#include "hext/rule.h"


namespace hext {


rule::rule()
: children(),
  attributes(),
  tag_name()
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

void rule::set_tag_name(std::string name)
{
  this->tag_name = name;
}


} // namespace hext


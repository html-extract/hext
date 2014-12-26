#include "hext/attribute.h"


namespace hext {


attribute::attribute()
: name(),
  value(),
  capture(false),
  builtin(false)
{
}

std::string attribute::get_name() const
{
  return this->name;
}

std::string attribute::get_value() const
{
  return this->value;
}

bool attribute::is_capture() const
{
  return this->capture;
}

bool attribute::is_builtin() const
{
  return this->builtin;
}

void attribute::set_name(const std::string& attribute_name)
{
  this->name = attribute_name;
}

void attribute::set_value(const std::string& attribute_value)
{
  this->value = attribute_value;
}

void attribute::set_is_capture(bool capt)
{
  this->capture = capt;
}

void attribute::set_is_builtin(bool built)
{
  this->builtin = built;
}


} // namespace hext


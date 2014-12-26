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

bool attribute::get_is_capture() const
{
  return this->capture;
}

bool attribute::get_is_builtin() const
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

void attribute::set_is_capture(bool is_capture)
{
  this->capture = is_capture;
}

void attribute::set_is_builtin(bool is_builtin)
{
  this->builtin = is_builtin;
}


} // namespace hext


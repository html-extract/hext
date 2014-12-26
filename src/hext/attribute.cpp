#include "hext/attribute.h"


namespace hext {


attribute::attribute()
: name(),
  value(),
  is_capt(false),
  is_built(false)
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
  return this->is_capt;
}

bool attribute::is_builtin() const
{
  return this->is_built;
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
  this->is_capt = capt;
}

void attribute::set_is_builtin(bool built)
{
  this->is_built = built;
}

match_tree::name_value_pair
attribute::capture(const GumboNode * node) const
{
  if( node == nullptr )
    return match_tree::name_value_pair("", "");

  if( node->type != GUMBO_NODE_ELEMENT )
    return match_tree::name_value_pair("", "");

  if( this->name == "hext-inner-text" )
  {
    return match_tree::name_value_pair(
      /* name  */ this->value,
      /* value */ bc::capture_inner_text(node)
    );
  }
  else
  {
    GumboAttribute * g_attr = gumbo_get_attribute(
      &node->v.element.attributes,
      this->name.c_str()
    );
    return match_tree::name_value_pair(
      /* name  */ this->value,
      /* value */ ( g_attr && g_attr->value ? g_attr->value : "" )
    );
  }
}


} // namespace hext


#include "hext/attribute.h"


namespace hext {


attribute::attribute()
: name(),
  value(),
  is_capt(false),
  is_built(false)
{
}

bool attribute::is_capture() const
{
  return this->is_capt;
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

bool attribute::matches(const GumboNode * node) const
{
  if( node == nullptr )
    return false;

  if( node->type != GUMBO_NODE_ELEMENT )
    return false;

  if( this->is_built )
    return true;

  GumboAttribute * g_attr =
    gumbo_get_attribute(&node->v.element.attributes, this->name.c_str());

  if( !g_attr )
    return false;

  if( !this->is_capt && this->value.compare(g_attr->value) != 0 )
    return false;

  return true;
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

void attribute::print(std::ostream& out) const
{
  out << this->name
      << "=\""
      << ( this->is_capt ? "(:" : "" )
      << this->value
      << ( this->is_capt ? ")" : "" )
      << "\"";
}


} // namespace hext


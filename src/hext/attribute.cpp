#include "hext/attribute.h"


namespace hext {


attribute::attribute(
  const std::string& attr_name,
  const std::string& attr_value,
  bool capture_contents
)
: name(attr_name),
  value(attr_value),
  is_capt(capture_contents),
  is_built(attr_name.compare(0, 5, "hext-") == 0)
{
}

bool attribute::is_capture() const
{
  return this->is_capt;
}

bool attribute::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  if( this->is_built )
    return true;

  GumboAttribute * g_attr =
    gumbo_get_attribute(&node->v.element.attributes, this->name.c_str());

  if( !g_attr )
    return false;

  if( !this->is_capt )
  {
    boost::regex rx(this->value, boost::regex_constants::icase);
    return boost::regex_search(g_attr->value, rx);
  }

  return true;
}

match_tree::name_value_pair
attribute::capture(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
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


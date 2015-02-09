#include "hext/attribute-capture.h"


namespace hext {


attribute_capture::attribute_capture(
  const std::string& result_name,
  const std::string& attr_name,
  const std::string& regex
)
: capture_pattern(result_name, regex)
, attr(attr_name)
{
}

match_tree::name_value_pair
attribute_capture::capture(const GumboNode * node) const
{
  const GumboAttribute * g_attr = this->get_node_attr(node);

  if( !g_attr )
    return match_tree::name_value_pair(this->name, "");

  if( this->rx )
  {
    return match_tree::name_value_pair(
      this->name,
      this->regex_filter(g_attr->value)
    );
  }
  else
  {
    return match_tree::name_value_pair(this->name, g_attr->value);
  }
}

void attribute_capture::print(std::ostream& out) const
{
  out << ' ' << this->attr << "={" << this->name;
  if( this->rx )
    out << '/' << this->rx->str() << '/';
  out << '}';
}

const GumboAttribute *
attribute_capture::get_node_attr(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return nullptr;

  return gumbo_get_attribute(&node->v.element.attributes, this->attr.c_str());
}


} // namespace hext


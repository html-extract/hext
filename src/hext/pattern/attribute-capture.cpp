#include "hext/pattern/attribute-capture.h"


namespace hext {


AttributeCapture::AttributeCapture(
  const std::string& result_name,
  const std::string& attr_name,
  const std::string& regex
)
: CapturePattern(result_name, regex)
, attr(attr_name)
{
}

MatchTree::NameValuePair
AttributeCapture::capture(const GumboNode * node) const
{
  const GumboAttribute * g_attr = this->get_node_attr(node);

  if( !g_attr )
    return MatchTree::NameValuePair(this->name, "");

  if( this->rx )
  {
    return MatchTree::NameValuePair(
      this->name,
      this->regex_filter(g_attr->value)
    );
  }
  else
  {
    return MatchTree::NameValuePair(this->name, g_attr->value);
  }
}

void AttributeCapture::print(std::ostream& out) const
{
  out << ' ' << this->attr << "={" << this->name;
  if( this->rx )
    out << '/' << this->rx->str() << '/';
  out << '}';
}

const GumboAttribute *
AttributeCapture::get_node_attr(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return nullptr;

  return gumbo_get_attribute(&node->v.element.attributes, this->attr.c_str());
}


} // namespace hext


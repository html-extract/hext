#include "hext/pattern/attribute-match.h"


namespace hext {


attribute_match::attribute_match(
  const std::string& attr_name,
  std::unique_ptr<attr_test> attribute_test
)
: match_pattern(std::move(attribute_test))
, attr(attr_name)
{
}

match_result attribute_match::matches(const GumboNode * node) const
{
  const GumboAttribute * g_attr = this->get_node_attr(node);
  if( !g_attr )
    return match_result(false, nullptr);
  if( !this->test || this->test->test(g_attr->value) )
    return match_result(true, g_attr);
  else
    return match_result(false, nullptr);
}

void attribute_match::print(std::ostream& out) const
{
  out << " " << this->attr;
  if( this->test )
    this->test->print(out);
}

const GumboAttribute *
attribute_match::get_node_attr(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return nullptr;

  return gumbo_get_attribute(&node->v.element.attributes, this->attr.c_str());
}


} // namespace hext


#include "hext/pattern/attribute-match.h"


namespace hext {


AttributeMatch::AttributeMatch(
  const std::string& attr_name,
  std::unique_ptr<AttrTest> attribute_test
)
: MatchPattern(std::move(attribute_test))
, attr(attr_name)
{
}

MatchResult AttributeMatch::matches(const GumboNode * node) const
{
  const GumboAttribute * g_attr = this->get_node_attr(node);
  if( !g_attr )
    return MatchResult(false, nullptr);
  if( !this->test || this->test->test(g_attr->value) )
    return MatchResult(true, g_attr);
  else
    return MatchResult(false, nullptr);
}

void AttributeMatch::print(std::ostream& out) const
{
  out << " " << this->attr;
  if( this->test )
    this->test->print(out);
}

const GumboAttribute *
AttributeMatch::get_node_attr(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return nullptr;

  return gumbo_get_attribute(&node->v.element.attributes, this->attr.c_str());
}


} // namespace hext


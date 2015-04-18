#include "hext/pattern/AttributeMatch.h"


namespace hext {


AttributeMatch::AttributeMatch(
  const std::string& attr_name,
  std::unique_ptr<test::ValueTest> value_test
)
: ValueMatch(std::move(value_test))
, attr_name_(attr_name)
{
}

bool AttributeMatch::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  const GumboAttribute * g_attr = gumbo_get_attribute(
    &node->v.element.attributes,
    this->attr_name_.c_str()
  );

  if( !g_attr )
    return false;

  if( !this->test_ || this->test_->test(g_attr->value) )
    return true;

  return false;
}


} // namespace hext


#include "hext/pattern/AttributeMatch.h"
#include "hext/MakeUnique.h"

#include <cassert>


namespace hext {


AttributeMatch::AttributeMatch(
  std::string attr_name,
  std::unique_ptr<ValueTest> value_test
)
: attr_name_(std::move(attr_name))
, test_(std::move(value_test))
{
}

bool AttributeMatch::matches(const GumboNode * node) const
{
  assert(node);
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  const GumboAttribute * g_attr = gumbo_get_attribute(
    &node->v.element.attributes,
    this->attr_name_.c_str()
  );

  if( !this->test_ )
    return g_attr;

  if( !g_attr )
    return (*this->test_)(nullptr);
  else if( g_attr->value )
    return (*this->test_)(g_attr->value);
  else
    return false;
}


} // namespace hext


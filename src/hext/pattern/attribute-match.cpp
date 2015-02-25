#include "hext/pattern/attribute-match.h"


namespace hext {


AttributeMatch::AttributeMatch(
  const std::string& attr_name,
  std::unique_ptr<AttrTest> attribute_test
)
: MatchPattern(std::move(attribute_test))
, attr_(attr_name)
{
}

MatchResult AttributeMatch::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return MatchResult(false, nullptr);

  const GumboAttribute * g_attr = gumbo_get_attribute(
    &node->v.element.attributes,
    this->attr_.c_str()
  );

  if( !g_attr )
    return MatchResult(false, nullptr);

  if( !this->test_ || this->test_->test(g_attr->value) )
    return MatchResult(true, g_attr);

  return MatchResult(false, nullptr);
}

void AttributeMatch::print(std::ostream& out) const
{
  out << " " << this->attr_;
  if( this->test_ )
    this->test_->print(out);
}


} // namespace hext


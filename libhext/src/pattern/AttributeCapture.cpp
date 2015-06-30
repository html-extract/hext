#include "hext/pattern/AttributeCapture.h"


namespace hext {


AttributeCapture::AttributeCapture(
  std::string attr_name,
  std::string result_name,
  boost::optional<boost::regex> regex
)
: CapturePattern(std::move(result_name), std::move(regex))
, attr_name_(std::move(attr_name))
{
}

ResultPair AttributeCapture::capture(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return ResultPair(this->name_, "");

  const GumboAttribute * g_attr = gumbo_get_attribute(
    &node->v.element.attributes,
    this->attr_name_.c_str()
  );

  if( !g_attr )
    return ResultPair(this->name_, "");

  if( this->rx_ )
  {
    return ResultPair(
      this->name_,
      this->regex_filter(g_attr->value)
    );
  }
  else
  {
    return ResultPair(this->name_, g_attr->value);
  }
}


} // namespace hext


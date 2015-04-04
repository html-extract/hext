#include "hext/pattern/AttributeCapture.h"


namespace hext {


AttributeCapture::AttributeCapture(
  const std::string& result_name,
  const std::string& attr_name
)
: CapturePattern(result_name)
, attr_name_(attr_name)
{
}

AttributeCapture::AttributeCapture(
  const std::string& result_name,
  const std::string& attr_name,
  const boost::regex& regex
)
: CapturePattern(result_name, regex)
, attr_name_(attr_name)
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


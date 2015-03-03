#include "hext/pattern/attribute-capture.h"


namespace hext {


AttributeCapture::AttributeCapture(
  const std::string& result_name,
  const std::string& attr_name
)
: CapturePattern(result_name)
, attr_(attr_name)
{
}

AttributeCapture::AttributeCapture(
  const std::string& result_name,
  const std::string& attr_name,
  const boost::regex& regex
)
: CapturePattern(result_name, regex)
, attr_(attr_name)
{
}

MatchTree::NameValuePair
AttributeCapture::capture(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return MatchTree::NameValuePair(this->name_, "");

  const GumboAttribute * g_attr = gumbo_get_attribute(
    &node->v.element.attributes,
    this->attr_.c_str()
  );

  if( !g_attr )
    return MatchTree::NameValuePair(this->name_, "");

  if( this->rx_ )
  {
    return MatchTree::NameValuePair(
      this->name_,
      this->regex_filter(g_attr->value)
    );
  }
  else
  {
    return MatchTree::NameValuePair(this->name_, g_attr->value);
  }
}

void AttributeCapture::print(std::ostream& out) const
{
  out << ' ' << this->attr_ << "={" << this->name_;
  if( this->rx_ )
    out << '/' << this->rx_->str() << '/';
  out << '}';
}


} // namespace hext


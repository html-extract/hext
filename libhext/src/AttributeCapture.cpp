#include "hext/AttributeCapture.h"

#include <cassert>
#include <utility>


namespace hext {


AttributeCapture::AttributeCapture(
  std::string attr_name,
  std::string result_name,
  boost::optional<boost::regex> filter
)
: attr_name_(std::move(attr_name))
, name_(std::move(result_name))
, filter_(std::move(filter))
{
}

boost::optional<ResultPair>
AttributeCapture::capture(const GumboNode * node) const
{
  assert(node);
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return {};

  const GumboAttribute * g_attr = gumbo_get_attribute(
    &node->v.element.attributes,
    this->attr_name_.c_str()
  );

  if( !g_attr || !g_attr->value )
    return {};

  if( this->filter_ )
  {
    boost::match_results<const char *> mr;
    if( boost::regex_search(g_attr->value, mr, this->filter_.get()) )
    {
      // If there are no parentheses contained within the regex, return whole
      // regex capture (mr[0]), if there are, then return the first one.
      return ResultPair(
        this->name_,
        mr.size() > 1 ? mr[1] : mr[0]
      );
    }
    else
    {
      return {};
    }
  }
  else
  {
    return ResultPair(this->name_, g_attr->value);
  }
}


} // namespace hext


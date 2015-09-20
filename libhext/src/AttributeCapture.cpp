#include "hext/AttributeCapture.h"

#include <cassert>
#include <utility>


namespace hext {


AttributeCapture::AttributeCapture(std::string                 attr_name,
                                   std::string                 result_name,
                                   std::unique_ptr<StringPipe> pipe)
: attr_name_(std::move(attr_name))
, name_(std::move(result_name))
, pipe_(std::move(pipe))
{
}

AttributeCapture::AttributeCapture(const AttributeCapture& other)
: attr_name_(other.attr_name_)
, name_(other.name_)
, pipe_(other.pipe_ ? other.pipe_->clone() : nullptr)
{
}

AttributeCapture& AttributeCapture::operator=(const AttributeCapture& other)
{
  if( this != &other )
  {
    this->attr_name_ = other.attr_name_;
    this->name_ = other.name_;
    this->pipe_ = std::move(other.pipe_->clone());
  }

  return *this;
}

boost::optional<ResultPair> AttributeCapture::capture(
    const GumboNode * node) const
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

  if( this->pipe_ )
    return ResultPair(
        this->name_,
        this->pipe_->pipe(g_attr->value)
    );

  return ResultPair(this->name_, g_attr->value);
}


} // namespace hext


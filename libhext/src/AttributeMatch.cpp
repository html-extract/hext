#include "hext/AttributeMatch.h"

#include <algorithm>
#include <cassert>
#include <utility>


namespace hext {


AttributeMatch::AttributeMatch(std::string                attr_name,
                               std::unique_ptr<ValueTest> value_test) noexcept
: attr_name_(std::move(attr_name))  // noexcept
, test_(std::move(value_test))      // noexcept
{
}

AttributeMatch::~AttributeMatch() = default;
AttributeMatch::AttributeMatch(AttributeMatch&& other) = default;

AttributeMatch::AttributeMatch(const AttributeMatch& other)
: attr_name_(other.attr_name_)
, test_(other.test_ ? other.test_->clone() : nullptr)
{
}

AttributeMatch& AttributeMatch::operator=(AttributeMatch&& other) = default;

AttributeMatch& AttributeMatch::operator=(const AttributeMatch& other)
{
  using std::swap;
  AttributeMatch tmp(other);
  swap(*this, tmp);
  return *this;
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
    return this->test_->test(nullptr);
  else if( g_attr->value )
    return this->test_->test(g_attr->value);
  else
    return false;
}


} // namespace hext


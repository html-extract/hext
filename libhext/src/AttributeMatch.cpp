// Copyright 2015, 2016 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

AttributeMatch::AttributeMatch(const AttributeMatch& other)
: attr_name_(other.attr_name_)
, test_(other.test_ ? other.test_->clone() : nullptr)
{
}

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
    return g_attr != nullptr;

  if( !g_attr )
    return this->test_->test(nullptr);
  else if( g_attr->value )
    return this->test_->test(g_attr->value);
  else
    return false;
}


} // namespace hext


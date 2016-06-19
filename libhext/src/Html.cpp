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

#include "hext/Html.h"

#include <cstring>


namespace hext {


Html::Html(const char * buffer, std::size_t size) noexcept
: g_outp_(
      gumbo_parse_with_options(&kGumboDefaultOptions,
                               buffer,
                               size))  // noexcept
{
}

Html::Html(const char * buffer) noexcept
: g_outp_(
      gumbo_parse_with_options(&kGumboDefaultOptions,
                               buffer,
                               std::strlen(buffer)))  // noexcept
{
}

Html::~Html() noexcept
{
  if( this->g_outp_ )
    gumbo_destroy_output(&kGumboDefaultOptions, this->g_outp_);
}

const GumboNode * Html::root() const noexcept
{
  return this->g_outp_ ? this->g_outp_->root : nullptr;
}


} // namespace hext


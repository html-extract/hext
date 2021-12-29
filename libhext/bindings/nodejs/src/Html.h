// Copyright 2016-2021 Thomas Trapp
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

#ifndef HTML_H_INCLUDED
#define HTML_H_INCLUDED

#include <hext/Html.h>

#include <gumbo.h>
#include <napi.h>

#include <memory>
#include <string>


class Html : public Napi::ObjectWrap<Html>
{
public:
  explicit Html(const Napi::CallbackInfo&);
  static Napi::Function GetClass(Napi::Env);
  const GumboNode * root() const
  {
    if( !this->html_ )
      return nullptr;

    return this->html_->root();
  }

  static constexpr napi_type_tag type_tag = {
    0x2fedb12d29f14223,
    0x997e3d5f87ab7dd0
  };

private:
  std::string buffer_;
  std::unique_ptr<hext::Html> html_;
};


#endif // HTML_H_INCLUDED


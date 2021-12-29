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

#include "Html.h"


Html::Html(const Napi::CallbackInfo& info)
: ObjectWrap(info)
, buffer_()
, html_(nullptr)
{
  Napi::Env env = info.Env();

  if( info.Length() < 1 )
  {
    Napi::TypeError::New(
        env,
        "Argument error: invalid argument, expected String")
      .ThrowAsJavaScriptException();
    return;
  }

  if( !info[0].IsString() )
  {
    Napi::TypeError::New(
        env,
        "Argument error: missing argument, expected String")
      .ThrowAsJavaScriptException();
    return;
  }

  auto status = napi_type_tag_object(env, this->Value(), &(this->type_tag));
  if( status != napi_ok )
  {
    Napi::Error::New(
        env,
        "Internal error: type tagging failed")
      .ThrowAsJavaScriptException();
    return;
  }

  this->buffer_ = info[0].As<Napi::String>().Utf8Value();
  this->html_ = std::make_unique<hext::Html>(
      this->buffer_.c_str(), this->buffer_.size());
}

Napi::Function Html::GetClass(Napi::Env env)
{
  using namespace Napi;
  return DefineClass(env, "Html", {});
}


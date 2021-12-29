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

#include "Rule.h"
#include "Html.h"

#include <hext/MaxSearchError.h>
#include <hext/ParseHext.h>
#include <hext/Result.h>

#include <cstdint>


Rule::Rule(const Napi::CallbackInfo& info)
: ObjectWrap(info)
, rule_(nullptr)
{
  Napi::Env env = info.Env();

  if( info.Length() < 1 )
  {
    Napi::TypeError::New(
        env,
        "Argument error: missing argument, expected String")
      .ThrowAsJavaScriptException();
    return;
  }

  if( !info[0].IsString() )
  {
    Napi::TypeError::New(
        env,
        "Argument error: invalid argument, expected String")
      .ThrowAsJavaScriptException();
    return;
  }

  try
  {
    this->rule_ = std::make_unique<hext::Rule>(
        hext::ParseHext(info[0].As<Napi::String>().Utf8Value().c_str()));
  }
  catch( const hext::SyntaxError& e )
  {
    auto message = std::string("Hext syntax error: ") + e.what();
    Napi::Error::New(env, message).ThrowAsJavaScriptException();
    return;
  }
}

Napi::Value Rule::extract(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  if( !this->rule_ )
  {
    Napi::TypeError::New(
        env,
        "Internal Error: rule_ is uninitialized")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if( info.Length() < 1 )
  {
    Napi::TypeError::New(
        env,
        "Argument error: missing argument, expected hext.Html")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  std::uint64_t max_searches = 0;
  if( info.Length() > 1 )
  {
    if( !info[1].IsNumber() )
    {
      Napi::TypeError::New(
          env,
          "Argument error: Optional argument 'max_searches' must be "
          "a number")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    else
    {
      max_searches = info[1].ToNumber().Uint32Value();
    }
  }

  auto obj = info[0].As<Napi::Object>();
  bool type_tag_matches = false;

  {
    auto status = napi_check_object_type_tag(
        env, obj, &(Html::type_tag), &type_tag_matches);

    if( status != napi_ok )
    {
      Napi::Error::New(
          env,
          "Internal error: napi_check_object_type_tag failed")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
  }

  Html * html = nullptr;
  if( type_tag_matches )
    html = Napi::ObjectWrap<Html>::Unwrap(obj);

  if( !html )
  {
    Napi::TypeError::New(
        env,
        "Argument error: invalid argument, expected hext.Html")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if( !html->root() )
  {
    Napi::TypeError::New(
        env,
        "Internal Error: html_ is uninitialized")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  hext::Result result;
  try
  {
    result = this->rule_->extract(html->root(), max_searches);
  }
  catch( const hext::MaxSearchError& e )
  {
    auto message = std::string("Error: ") + e.what();
    Napi::Error::New(
        env,
        message)
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Array ret = Napi::Array::New(env);
  for(const auto& group : result)
  {
    Napi::Object map = Napi::Object::New(env);
    auto it = group.cbegin();
    while( it != group.cend() )
    {
      if( group.count(it->first) < 2 )
      {
        map.Set(
            Napi::String::New(env, it->first),
            Napi::String::New(env, it->second));
        ++it;
      }
      else
      {
        // Pack values of non-unique keys into an indexed array
        Napi::Array array = Napi::Array::New(env);
        auto lower = group.lower_bound(it->first);
        auto upper = group.upper_bound(it->first);
        for(; lower != upper; ++lower)
          array.Set(
              array.Length(),
              Napi::String::New(env, lower->second));
        map.Set(
            Napi::String::New(env, it->first),
            array);
        it = upper;
      }
    }

    ret.Set(ret.Length(), map);
  }

  return ret;
}

Napi::Function Rule::GetClass(Napi::Env env)
{
  using namespace Napi;
  return DefineClass(
    env,
    "Rule",
    {
      Rule::InstanceMethod("extract", &Rule::extract),
    });
}


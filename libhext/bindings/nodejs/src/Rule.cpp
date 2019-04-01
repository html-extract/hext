// Copyright 2016 Thomas Trapp
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

#include <hext/ParseHext.h>

#include <utility>


Nan::Persistent<v8::Function> Rule::constructor;

NAN_MODULE_INIT(Rule::Init)
{
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Rule").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "extract", extract);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target,
           Nan::New("Rule").ToLocalChecked(),
           Nan::GetFunction(tpl).ToLocalChecked());
}

Rule::Rule(hext::Rule rule)
: rule_(std::move(rule))
{
}

NAN_METHOD(Rule::New)
{
  if( info.IsConstructCall() )
  {
    Rule * obj = nullptr;
    if( info[0]->IsString() )
    {
      Nan::Utf8String arg(info[0]);
      try
      {
        obj = new Rule(hext::ParseHext(*arg == nullptr ? "" : *arg));
      }
      catch( const hext::SyntaxError& e )
      {
        auto message = std::string("Hext syntax error: ") + e.what();
        Nan::ThrowError(Nan::New<v8::String>(message.c_str()).ToLocalChecked());
        return;
      }
    }
    else if( info[0]->IsUndefined() )
    {
      Nan::ThrowTypeError(
          Nan::New<v8::String>("Argument error: missing argument, "
                               "expected String").ToLocalChecked());
      return;
    }
    else
    {
      Nan::ThrowTypeError(
          Nan::New<v8::String>("Argument error: invalid argument type, "
                               "expected String").ToLocalChecked());
      return;
    }

    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  }
  else
  {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New(constructor);
    info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
  }
}

NAN_METHOD(Rule::extract) {
  Rule * obj = Nan::ObjectWrap::Unwrap<Rule>(info.This());
  Nan::MaybeLocal<v8::Object> maybe_arg = Nan::To<v8::Object>(info[0]);
  if( maybe_arg.IsEmpty() )
  {
    Nan::ThrowTypeError(
        Nan::New<v8::String>("Argument error: missing argument, "
                             "expected hext.Html").ToLocalChecked());
    return;
  }

  Html * arg = Nan::ObjectWrap::Unwrap<Html>(maybe_arg.ToLocalChecked());
  if( !arg )
  {
    Nan::ThrowTypeError(
        Nan::New<v8::String>("Argument error: invalid argument type, "
                             "expected hext.Html").ToLocalChecked());
    return;
  }

  auto result = obj->rule_.extract(arg->root());
  v8::Local<v8::Array> ret = Nan::New<v8::Array>();
  for(const auto& group : result)
  {
    v8::Local<v8::Object> map = Nan::New<v8::Object>();
    auto it = group.cbegin();
    while( it != group.cend() )
    {
      if( group.count(it->first) < 2 )
      {
        map->Set(
          Nan::New<v8::String>(it->first).ToLocalChecked(),
          Nan::New<v8::String>(it->second).ToLocalChecked()
        );
        ++it;
      }
      else
      {
        // Pack values of non-unique keys into an indexed array
        v8::Local<v8::Array> array = Nan::New<v8::Array>();
        auto lower = group.lower_bound(it->first);
        auto upper = group.upper_bound(it->first);
        for(; lower != upper; ++lower)
          array->Set(
              array->Length(),
              Nan::New<v8::String>(lower->second).ToLocalChecked());
        map->Set(
          Nan::New<v8::String>(it->first).ToLocalChecked(),
          array
        );
        it = upper;
      }
    }

    ret->Set(ret->Length(), map);
  }
  info.GetReturnValue().Set(ret);
}


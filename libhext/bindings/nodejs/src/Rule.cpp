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
    if( info[0]->IsUndefined() )
    {
      obj = new Rule(hext::ParseHext(""));
    }
    else
    {
      Nan::Utf8String arg(info[0]);
      obj = new Rule(hext::ParseHext(*arg == nullptr ? "" : *arg));
    }

    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  }
  else
  {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

NAN_METHOD(Rule::extract) {
  Rule * obj = Nan::ObjectWrap::Unwrap<Rule>(info.This());
  Nan::MaybeLocal<v8::Object> maybe_arg = Nan::To<v8::Object>(info[0]);
  if( maybe_arg.IsEmpty() )
    return;

  Html * arg = Nan::ObjectWrap::Unwrap<Html>(maybe_arg.ToLocalChecked());
  auto result = obj->rule_.extract(arg->root());
  v8::Local<v8::Array> ret = Nan::New<v8::Array>();
  for(const auto& group : result)
  {
    v8::Local<v8::Array> map = Nan::New<v8::Array>();
    for(const auto& pair : group)
      map->Set(
        Nan::New<v8::String>(pair.first).ToLocalChecked(),
        Nan::New<v8::String>(pair.second).ToLocalChecked()
      );

    ret->Set(ret->Length(), map);
  }
  info.GetReturnValue().Set(ret);
}


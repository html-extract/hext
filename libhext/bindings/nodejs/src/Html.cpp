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

#include "Html.h"

#include <utility>


Nan::Persistent<v8::Function> Html::constructor;

NAN_MODULE_INIT(Html::Init)
{
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Html").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target,
           Nan::New("Html").ToLocalChecked(),
           Nan::GetFunction(tpl).ToLocalChecked());
}

Html::Html(std::string html)
: buffer_(std::move(html))
, html_(buffer_.c_str(), buffer_.size())
{
}

NAN_METHOD(Html::New)
{
  if( info.IsConstructCall() )
  {
    Html * obj = nullptr;
    if( info[0]->IsString() )
    {
      Nan::Utf8String arg(info[0]);
      if( !*arg )
      {
        Nan::ThrowTypeError(
            Nan::New<v8::String>("Argument error: invalid argument, "
                                 "expected String").ToLocalChecked());
        return;
      }

      obj = new Html(std::string(*arg));
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


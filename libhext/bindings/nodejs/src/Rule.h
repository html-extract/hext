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

#ifndef RULE_H_INCLUDED
#define RULE_H_INCLUDED

#include <hext/Rule.h>

#include <nan.h>


class Rule : public Nan::ObjectWrap
{
public:
  static NAN_MODULE_INIT(Init);

private:
  explicit Rule(hext::Rule rule);
  ~Rule() = default;
  static NAN_METHOD(New);
  static NAN_METHOD(extract);
  static Nan::Persistent<v8::Function> constructor;

  hext::Rule rule_;
};


#endif // RULE_H_INCLUDED


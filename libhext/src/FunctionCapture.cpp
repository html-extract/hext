// Copyright 2015-2017 Thomas Trapp
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

#include "hext/FunctionCapture.h"

#include <cassert>
#include <utility>


namespace hext {


FunctionCapture::FunctionCapture(CaptureFunction             func,
                                 std::string                 result_name,
                                 std::unique_ptr<StringPipe> pipe) noexcept
: func_(std::move(func))
, name_(std::move(result_name))
, pipe_(std::move(pipe))
{
}

FunctionCapture::FunctionCapture(const FunctionCapture& other)
: func_(other.func_)
, name_(other.name_)
, pipe_(other.pipe_ ? other.pipe_->clone() : nullptr)
{
}

FunctionCapture& FunctionCapture::operator=(const FunctionCapture& other)
{
  if( this != &other )
  {
    this->func_ = other.func_;
    this->name_ = other.name_;
    this->pipe_ = other.pipe_->clone();
  }

  return *this;
}

std::optional<ResultPair> FunctionCapture::capture(const GumboNode * node) const
{
  assert(this->func_);
  if( !this->func_ )
    return {};

  auto str = this->func_(node);

  if( this->pipe_ )
    return ResultPair(
        this->name_,
        this->pipe_->pipe(std::move(str))
    );

  return ResultPair(this->name_, str);
}


} // namespace hext


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

#include "hext/StringPipe.h"


namespace hext {


StringPipe::StringPipe() noexcept
: next_(nullptr)
{
}

StringPipe::StringPipe(const StringPipe& other)
: next_(other.next_ ? other.next_->clone() : nullptr)
{
}

StringPipe& StringPipe::operator=(const StringPipe& other)
{
  if( this != &other )
  {
    // delete current chain
    this->next_ = nullptr;

    // recursively clone the pipe chain (Cloneable::clone() will call the copy
    // ctor for other.next_).
    if( other.next_ )
      this->next_ = other.next_->clone();
  }

  return *this;
}

std::string StringPipe::pipe(std::string str) const
{
  str = this->transform(std::move(str));

  if( this->next_ )
    str = this->next_->pipe(std::move(str));

  return str;
}

void StringPipe::append(std::unique_ptr<StringPipe> p) noexcept
{
  if( this->next_ )
    // recursively move p to the end of the chain
    this->next_->append(std::move(p));
  else
    this->next_.swap(p);
}


} // namespace hext


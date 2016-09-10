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

#ifndef HEXT_STRING_PIPE_H_INCLUDED
#define HEXT_STRING_PIPE_H_INCLUDED

/// @file
///   Declares hext::StringPipe

#include "hext/Visibility.h"

#include <memory>
#include <string>
#include <utility>


namespace hext {


/// Abstract base for every StringPipe. A StringPipe transforms a given
/// string into another one, for example a TrimPipe removes all left and right
/// whitespace from a string. StringPipes can be chained ("linked list").
///
/// Note: You probably don't want to inherit from this class directly, unless
///       you want to provide your own StringPipe::clone() method. If your
///       subclass has a copy constructor, you can extend from
///       hext::Cloneable<YourSubclass, hext::StringPipe> which provides a
///       generic clone method.
class HEXT_PUBLIC StringPipe
{
public:
  StringPipe() noexcept;
  StringPipe(const StringPipe& other);
  StringPipe(StringPipe&&) noexcept = default;
  StringPipe& operator=(const StringPipe& other);
  StringPipe& operator=(StringPipe&&) noexcept = default;
  virtual ~StringPipe() noexcept = default;

  /// Clones derived object.
  virtual std::unique_ptr<StringPipe> clone() const = 0;

  /// Transforms str.
  ///
  /// Note: Use StringPipe::pipe to apply all transformations in this chain.
  virtual std::string transform(std::string str) const = 0;

  /// Calls StringPipe::transform successively until the whole StringPipe chain
  /// was traversed.
  ///
  /// @returns  The result of applying this StringPipe and every connected
  ///           one to str.
  std::string pipe(std::string str) const;

  /// Append a StringPipe at the end of the chain.
  void append(std::unique_ptr<StringPipe> pipe) noexcept;

  /// Construct a StringPipe at the end of the chain.
  template<typename StringPipeType, typename... Args>
  void emplace(Args&&... arg)
  {
    this->append(std::make_unique<StringPipeType>(std::forward<Args>(arg)...));
  }

private:
  /// The next StringPipe in this chain.
  std::unique_ptr<StringPipe> next_;
};


} // namespace hext


#endif // HEXT_STRING_PIPE_H_INCLUDED


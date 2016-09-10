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

#ifndef HEXT_CONTAINS_WORDS_TEST_H_INCLUDED
#define HEXT_CONTAINS_WORDS_TEST_H_INCLUDED

/// @file
///   Declares hext::ContainsWordsTest

#include "hext/Cloneable.h"
#include "hext/ValueTest.h"
#include "hext/Visibility.h"

#include <string>
#include <vector>


namespace hext {


/// Tests whether a string contains all given words.
/// Word boundaries are the beginning and end of subject, and spaces.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   ContainsWordTest cw("foo baz bar");
///
///   assert( cw.test("bar baz foo"));
///   assert( cw.test("bar boing baz foo boing"));
///   assert(!cw.test("foobaz bar"));
///   assert(!cw.test("foo bar"));
/// ~~~~~~~~~~~~~
class HEXT_PUBLIC ContainsWordsTest final
  : public Cloneable<ContainsWordsTest, ValueTest>
{
public:
  /// Constructs a ContainsWordsTest that succeeds for subjects that contain all
  /// words given in a string.
  ///
  /// @param words:  A string that contains space-separated words.
  explicit ContainsWordsTest(std::string words);

  /// Constructs a ContainsWordsTest that succeeds for subjects that contain all
  /// words given in a vector.
  ///
  /// @param words:  A vector of words.
  explicit ContainsWordsTest(std::vector<std::string> words) noexcept;

  /// Returns true if subject contains all given words.
  ///
  /// @param subject:  The string that is to be tested.
  bool test(const char * subject) const override;

private:
  /// A vector of words that a subject must contain.
  std::vector<std::string> words_;
};


} // namespace hext


#endif // HEXT_CONTAINS_WORDS_TEST_H_INCLUDED


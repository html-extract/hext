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

#ifndef HEXT_ENDS_WITH_TEST_H_INCLUDED
#define HEXT_ENDS_WITH_TEST_H_INCLUDED

/// @file
///   Declares hext::EndsWithTest

#include "hext/Cloneable.h"
#include "hext/ValueTest.h"
#include "hext/Visibility.h"

#include <string>


namespace hext {


/// Tests whether a string ends with a given literal.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   EndsWithTest ends("baz");
///
///   assert( ends.test("foobaz"));
///   assert( ends.test("baz"));
///   assert(!ends.test("foo"));
/// ~~~~~~~~~~~~~
class HEXT_PUBLIC EndsWithTest final : public Cloneable<EndsWithTest, ValueTest>
{
public:
  /// Constructs an EndsWithTest that succeeds for subjects that end with the
  /// given literal.
  ///
  /// @param literal:  A string that a subject must end with.
  explicit EndsWithTest(std::string literal) noexcept;

  /// Returns true if subject ends with the given literal.
  ///
  /// @param subject:  The string that is to be tested.
  bool test(const char * subject) const override;

private:
  /// The literal that must be matched.
  std::string lit_;
};


} // namespace hext


#endif // HEXT_ENDS_WITH_TEST_H_INCLUDED


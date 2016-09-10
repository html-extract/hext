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

#ifndef HEXT_CONTAINS_TEST_H_INCLUDED
#define HEXT_CONTAINS_TEST_H_INCLUDED

/// @file
///   Declares hext::ContainsTest

#include "hext/Cloneable.h"
#include "hext/ValueTest.h"
#include "hext/Visibility.h"

#include <string>


namespace hext {


/// Tests whether a string contains a given literal.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   ContainsTest contains("foo");
///
///   assert( contains.test("foo"));
///   assert( contains.test("barfoobar"));
///   assert(!contains.test("barfo"));
/// ~~~~~~~~~~~~~
class HEXT_PUBLIC ContainsTest final : public Cloneable<ContainsTest, ValueTest>
{
public:
  /// Constructs a ContainsTest that succeeds for subjects that contain the
  /// given literal.
  ///
  /// @param literal:  A string that a subject must contain.
  explicit ContainsTest(std::string literal) noexcept;

  /// Return true if subject contains the given literal.
  ///
  /// @param subject:  The string that is to be tested.
  bool test(const char * subject) const override;

private:
  /// The literal that must be matched.
  std::string lit_;
};


} // namespace hext


#endif // HEXT_CONTAINS_TEST_H_INCLUDED


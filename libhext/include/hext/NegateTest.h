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

#ifndef HEXT_NEGATE_TEST_H_INCLUDED
#define HEXT_NEGATE_TEST_H_INCLUDED

/// @file
///   Declares hext::NegateTest

#include "hext/Cloneable.h"
#include "hext/ValueTest.h"
#include "hext/Visibility.h"

#include <memory>


namespace hext {


/// Negates the result of another ValueTest.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   NegateTest not_foo(std::make_unique<EqualsTest>("foo"));
///
///   assert( not_foo.test("bar"));
///   assert( not_foo.test("baz"));
///   assert(!not_foo.test("foo"));
/// ~~~~~~~~~~~~~
class HEXT_PUBLIC NegateTest final : public Cloneable<NegateTest, ValueTest>
{
public:
  /// Constructs a NegateTest.
  ///
  /// @param value_test:  The ValueTest a subject has to fail.
  explicit NegateTest(std::unique_ptr<ValueTest> value_test) noexcept;

  ~NegateTest() noexcept override = default;
  NegateTest(NegateTest&& other) noexcept = default;
  NegateTest(const NegateTest& other);
  NegateTest& operator=(NegateTest&& other) noexcept = default;
  NegateTest& operator=(const NegateTest& other);

  /// Returns true if the given ValueTest fails for subject.
  ///
  /// @param subject:  The string that is to be tested.
  bool test(const char * subject) const override;

private:
  /// The ValueTest a subject has to fail.
  std::unique_ptr<ValueTest> test_;
};


} // namespace hext


#endif // HEXT_NEGATE_TEST_H_INCLUDED


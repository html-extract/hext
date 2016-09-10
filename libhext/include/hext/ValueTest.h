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

#ifndef HEXT_VALUE_TEST_H_INCLUDED
#define HEXT_VALUE_TEST_H_INCLUDED

/// @file
///   Declares hext::ValueTest

#include "hext/Visibility.h"

#include <memory>


namespace hext {


/// Abstract base for every ValueTest.
/// ValueTests determine whether a string passes a certain test.
///
/// Note: You probably don't want to inherit from this class directly, unless
///       you want to provide your own ValueTest::clone() method. If your
///       subclass has a copy constructor, you can extend from
///       hext::Cloneable<YourSubclass, hext::ValueTest> which provides a
///       generic clone method.
class HEXT_PUBLIC ValueTest
{
public:
  ValueTest() noexcept = default;
  ValueTest(const ValueTest&) = default;
  ValueTest(ValueTest&&) noexcept = default;
  ValueTest& operator=(const ValueTest&) = default;
  ValueTest& operator=(ValueTest&&) noexcept = default;
  virtual ~ValueTest() noexcept = default;

  /// Clones derived object.
  virtual std::unique_ptr<ValueTest> clone() const = 0;

  /// Returns true if subject passes this ValueTest.
  virtual bool test(const char * /* dummy */) const = 0;
};


} // namespace hext


#endif // HEXT_VALUE_TEST_H_INCLUDED


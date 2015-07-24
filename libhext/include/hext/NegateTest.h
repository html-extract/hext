#ifndef HEXT_NEGATE_TEST_H_INCLUDED
#define HEXT_NEGATE_TEST_H_INCLUDED

/// @file
///   Declares hext::NegateTest

#include "hext/ValueTest.h"

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
class NegateTest : public ValueTest
{
public:
  /// Constructs a NegateTest.
  ///
  /// @param value_test:  The ValueTest a subject has to fail.
  explicit NegateTest(std::unique_ptr<ValueTest> value_test) noexcept;

  /// Returns true if the given ValueTest fails for subject.
  ///
  /// @param subject:  The string that is to be tested.
  bool test(const char * subject) const final;

private:
  /// The ValueTest a subject has to fail.
  std::unique_ptr<ValueTest> value_test_;
};


} // namespace hext


#endif // HEXT_NEGATE_TEST_H_INCLUDED


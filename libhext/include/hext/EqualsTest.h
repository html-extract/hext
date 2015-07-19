#ifndef HEXT_EQUALS_TEST_H_INCLUDED
#define HEXT_EQUALS_TEST_H_INCLUDED

#include "hext/ValueTest.h"

#include <string>


namespace hext {


/// Tests whether a string equals a given literal.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   EqualsTest equals("foo");
///
///   assert( equals.test("foo"));
///   assert(!equals.test("foob"));
///   assert(!equals.test("bfoo"));
/// ~~~~~~~~~~~~~
class EqualsTest : public ValueTest
{
public:
  /// Constructs an EqualsTest that succeeds for subjects that equal a given
  /// literal.
  ///
  /// @param literal:  A string that a subject must equal.
  explicit EqualsTest(std::string literal);

  /// Returns true if subject equals literal.
  ///
  /// @param subject:  The string that is to be tested.
  bool test(const char * subject) const final;

private:
  /// The literal that must be matched.
  std::string lit_;
};


} // namespace hext


#endif // HEXT_EQUALS_TEST_H_INCLUDED


#ifndef HEXT_CONTAINS_TEST_H_INCLUDED
#define HEXT_CONTAINS_TEST_H_INCLUDED

/// @file
///   Declares hext::ContainsTest

#include "hext/ValueTest.h"

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
class ContainsTest : public ValueTest
{
public:
  /// Constructs a ContainsTest that succeeds for subjects that contain the
  /// given literal.
  ///
  /// @param literal:  A string that a subject must contain.
  explicit ContainsTest(std::string literal);

  /// Return true if subject contains the given literal.
  ///
  /// @param subject:  The string that is to be tested.
  bool test(const char * subject) const final;

private:
  /// The literal that must be matched.
  std::string lit_;
};


} // namespace hext


#endif // HEXT_CONTAINS_TEST_H_INCLUDED


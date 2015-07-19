#ifndef HEXT_ENDS_WITH_TEST_H_INCLUDED
#define HEXT_ENDS_WITH_TEST_H_INCLUDED

#include "hext/ValueTest.h"

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
class EndsWithTest : public ValueTest
{
public:
  /// Constructs an EndsWithTest that succeeds for subjects that end with the
  /// given literal.
  ///
  /// @param literal:  A string that a subject must end with.
  explicit EndsWithTest(std::string literal);

  /// Returns true if subject ends with the given literal.
  ///
  /// @param subject:  The string that is to be tested.
  bool test(const char * subject) const final;

private:
  /// The literal that must be matched.
  std::string lit_;
};


} // namespace hext


#endif // HEXT_ENDS_WITH_TEST_H_INCLUDED


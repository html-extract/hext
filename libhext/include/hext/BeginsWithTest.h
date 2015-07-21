#ifndef HEXT_BEGINS_WITH_TEST_H_INCLUDED
#define HEXT_BEGINS_WITH_TEST_H_INCLUDED

/// @file
///   Declares hext::BeginsWithTest

#include "hext/ValueTest.h"

#include <string>


namespace hext {


/// Tests whether a string begins with a given literal.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   BeginsWithTest begins("Start");
///
///   assert( begins.test("Startles your sleeping ears to hear"));
///   assert(!begins.test("startles your sleeping ears to hear"));
///   assert(!begins.test(""));
/// ~~~~~~~~~~~~~
class BeginsWithTest : public ValueTest
{
public:
  /// Constructs a BeginsWithTest that succeeds for subjects that begin with
  /// the given literal.
  ///
  /// @param literal:  A string that a subject must begin with.
  explicit BeginsWithTest(std::string literal) noexcept;

  /// Return true if subject begins with the given literal.
  ///
  /// @param subject:  The string that is to be tested.
  bool test(const char * subject) const final;

private:
  /// The literal that must be matched.
  std::string lit_;
};


} // namespace hext


#endif // HEXT_BEGINS_WITH_TEST_H_INCLUDED


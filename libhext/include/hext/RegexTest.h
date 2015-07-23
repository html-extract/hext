#ifndef HEXT_REGEX_TEST_H_INCLUDED
#define HEXT_REGEX_TEST_H_INCLUDED

/// @file
///   Declares hext::RegexTest

#include "hext/ValueTest.h"

#include <boost/regex.hpp>


namespace hext {


/// Tests whether another string matches a given regex.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   RegexTest has_number(boost::regex("\\d+"));
///   assert( has_number.test("Nr. 23!"));
///   assert( has_number.test("23"));
///   assert(!has_number.test("foo"));
///
///   RegexTest is_date(boost::regex("^\\d{2}-\\d{2}-\\d{4}$"));
///   assert( is_date.test("01-01-1970"));
///   assert( is_date.test("19-01-2038"));
///   assert(!is_date.test("09-09-99"));
///   assert(!is_date.test("Born on 09-09-1941."));
/// ~~~~~~~~~~~~~
class RegexTest : public ValueTest
{
public:
  /// Constructs a RegexTest that succeeds if a subject matches regex.
  explicit RegexTest(boost::regex regex);

  /// Returns true if given regex matches subject.
  bool test(const char * subject) const final;

private:
  /// The regex a subject has to match.
  boost::regex rx_;
};


} // namespace hext


#endif // HEXT_REGEX_TEST_H_INCLUDED


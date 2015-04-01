#ifndef HEXT_PATTERN_IS_NOT_REGEX_TEST_H_INCLUDED
#define HEXT_PATTERN_IS_NOT_REGEX_TEST_H_INCLUDED

#include "hext/pattern/ValueTest.h"

#include <boost/regex.hpp>


namespace hext {


/// An IsNotRegexTest is a ValueTest that checks whether another string does
/// not match a given regex.
class IsNotRegexTest : public ValueTest
{
public:
  explicit IsNotRegexTest(const boost::regex& regex);

  /// Return true if regex does not match subject.
  bool test(const char * subject) const final;

private:
  const boost::regex rx_;
};


} // namespace hext


#endif // HEXT_PATTERN_IS_NOT_REGEX_TEST_H_INCLUDED


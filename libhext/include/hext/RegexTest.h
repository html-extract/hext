#ifndef HEXT_REGEX_TEST_H_INCLUDED
#define HEXT_REGEX_TEST_H_INCLUDED

#include "hext/ValueTest.h"

#include <boost/regex.hpp>


namespace hext {


/// Test whether another string matches a given regex.
class RegexTest : public ValueTest
{
public:
  explicit RegexTest(boost::regex regex);

  /// Return true if regex matches subject.
  bool test(const char * subject) const final;

private:
  boost::regex rx_;
};


} // namespace hext


#endif // HEXT_REGEX_TEST_H_INCLUDED


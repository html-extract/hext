#ifndef HEXT_PATTERN_REGEX_TEST_H_INCLUDED
#define HEXT_PATTERN_REGEX_TEST_H_INCLUDED

#include "hext/pattern/value-test.h"

#include <string>
#include <iostream>

#include <boost/regex.hpp>


namespace hext {


/// A RegexTest is a ValueTest that checks whether another string matches a
/// given regex.
class RegexTest : public ValueTest
{
public:
  explicit RegexTest(const std::string& regex);
  /// Returns true if regex matches subject.
  bool test(const char * subject) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const boost::regex rx_;
};


} // namespace hext


#endif // HEXT_PATTERN_REGEX_TEST_H_INCLUDED


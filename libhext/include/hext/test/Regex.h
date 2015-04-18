#ifndef HEXT_TEST_REGEX_H_INCLUDED
#define HEXT_TEST_REGEX_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <boost/regex.hpp>


namespace hext {
namespace test {


/// Regex is a ValueTest that checks whether another string matches a given
/// regex.
class Regex : public ValueTest
{
public:
  explicit Regex(const boost::regex& regex);

  /// Returns true if regex matches subject.
  bool operator()(const char * subject) const final;

private:
  const boost::regex rx_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_REGEX_H_INCLUDED


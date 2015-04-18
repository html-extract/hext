#ifndef HEXT_TEST_IS_NOT_REGEX_H_INCLUDED
#define HEXT_TEST_IS_NOT_REGEX_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <boost/regex.hpp>


namespace hext {
namespace test {


/// IsNotRegex is a ValueTest that checks whether another string does not match
/// a given regex.
class IsNotRegex : public ValueTest
{
public:
  explicit IsNotRegex(const boost::regex& regex);

  /// Return true if regex does not match subject.
  bool operator()(const char * subject) const final;

private:
  const boost::regex rx_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_IS_NOT_REGEX_H_INCLUDED


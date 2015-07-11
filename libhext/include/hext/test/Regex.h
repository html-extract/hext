#ifndef HEXT_TEST_REGEX_H_INCLUDED
#define HEXT_TEST_REGEX_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <boost/regex.hpp>


namespace hext {
namespace test {


/// Check whether another string matches a given regex.
class Regex : public ValueTest
{
public:
  explicit Regex(boost::regex regex)
  : rx_(std::move(regex))
    {}

  /// Returns true if regex matches subject.
  bool operator()(const char * subject) const final
  {
    if( !subject )
      return false;

    return boost::regex_search(subject, this->rx_);
  }

private:
  boost::regex rx_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_REGEX_H_INCLUDED


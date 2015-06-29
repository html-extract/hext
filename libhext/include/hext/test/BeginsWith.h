#ifndef HEXT_TEST_BEGINS_WITH_H_INCLUDED
#define HEXT_TEST_BEGINS_WITH_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <string>
#include <cstring>


namespace hext {
namespace test {


/// Check whether a string begins with a given literal.
class BeginsWith : public ValueTest
{
public:
  explicit BeginsWith(std::string literal)
  : lit_(std::move(literal))
    {}

  /// Return true if subject begins with literal.
  bool operator()(const char * subject) const final
  {
    if( !subject )
      return false;

    std::size_t length = std::strlen(subject);
    return
      this->lit_.size() <= length &&
      this->lit_.compare(0, this->lit_.size(), subject, this->lit_.size()) == 0;
  }

private:
  std::string lit_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_BEGINS_WITH_H_INCLUDED


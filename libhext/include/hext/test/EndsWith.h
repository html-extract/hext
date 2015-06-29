#ifndef HEXT_TEST_ENDS_WITH_H_INCLUDED
#define HEXT_TEST_ENDS_WITH_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <string>


namespace hext {
namespace test {


/// Check whether another string ends with a given literal.
class EndsWith : public ValueTest
{
public:
  explicit EndsWith(std::string literal)
  : lit_(std::move(literal))
    {}

  /// Return true if subject ends with literal.
  bool operator()(const char * subject) const final
  {
    if( !subject )
      return false;

    auto str = std::string(subject);

    if( this->lit_.size() > str.size() )
      return false;

    return std::equal(this->lit_.rbegin(), this->lit_.rend(), str.rbegin());
  }

private:
  std::string lit_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_ENDS_WITH_H_INCLUDED


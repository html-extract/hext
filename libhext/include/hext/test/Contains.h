#ifndef HEXT_TEST_CONTAINS_H_INCLUDED
#define HEXT_TEST_CONTAINS_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <string>


namespace hext {
namespace test {


/// Check whether a string is contained in another string.
class Contains : public ValueTest
{
public:
  explicit Contains(std::string literal)
  : lit_(std::move(literal))
    {}

  /// Return true if subject contains literal.
  bool operator()(const char * subject) const final
  {
    if( !subject )
      return false;

    auto str_subject = std::string(subject);
    return str_subject.find(this->lit_) != std::string::npos;
  }

private:
  std::string lit_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_CONTAINS_H_INCLUDED


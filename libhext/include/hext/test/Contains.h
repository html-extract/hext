#ifndef HEXT_TEST_CONTAINS_H_INCLUDED
#define HEXT_TEST_CONTAINS_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <string>


namespace hext {
namespace test {


/// Contains is a ValueTest that checks whether a string is contained in
/// another string.
class Contains : public ValueTest
{
public:
  explicit Contains(std::string literal);

  /// Return true if subject contains literal.
  bool operator()(const char * subject) const final;

private:
  std::string lit_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_CONTAINS_H_INCLUDED


#ifndef HEXT_TEST_ENDS_WITH_H_INCLUDED
#define HEXT_TEST_ENDS_WITH_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <string>


namespace hext {
namespace test {


/// EndsWith is a ValueTest that checks whether another string ends with a given
/// literal.
class EndsWith : public ValueTest
{
public:
  explicit EndsWith(std::string literal);

  /// Return true if subject ends with literal.
  bool operator()(const char * subject) const final;

private:
  const std::string lit_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_ENDS_WITH_H_INCLUDED


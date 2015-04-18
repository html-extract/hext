#ifndef HEXT_TEST_TRUE_H_INCLUDED
#define HEXT_TEST_TRUE_H_INCLUDED

#include "hext/test/ValueTest.h"


namespace hext {
namespace test {


/// True is a ValueTest that always returns true.
class True : public ValueTest
{
public:
  /// Return true.
  bool test(const char * /* dummy */) const final;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_TRUE_H_INCLUDED


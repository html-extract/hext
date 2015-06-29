#ifndef HEXT_TEST_NOT_NULL_H_INCLUDED
#define HEXT_TEST_NOT_NULL_H_INCLUDED

#include "hext/test/ValueTest.h"


namespace hext {
namespace test {


/// NotNull is a ValueTest that checks if subject is not nullptr.
class NotNull : public ValueTest
{
public:
  /// Return true if subject is not nullptr.
  bool operator()(const char * subject) const final
    { return subject != nullptr; }
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_NOT_NULL_H_INCLUDED


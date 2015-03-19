#ifndef HEXT_PATTERN_VALUE_TEST_H_INCLUDED
#define HEXT_PATTERN_VALUE_TEST_H_INCLUDED

#include <string>


namespace hext {


/// ValueTest is the base class for all pattern tests. Pattern tests are used
/// to validate attribute values of nodes according to a Rule's definition.
/// In its basic form it considers any value as valid.
/// See also LiteralTest and RegexTest.
class ValueTest
{
public:
  virtual ~ValueTest();
  /// Always return true.
  virtual bool test(const char * /* dummy */) const;
};


} // namespace hext


#endif // HEXT_PATTERN_VALUE_TEST_H_INCLUDED


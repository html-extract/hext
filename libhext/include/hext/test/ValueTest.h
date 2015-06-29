#ifndef HEXT_TEST_VALUE_TEST_H_INCLUDED
#define HEXT_TEST_VALUE_TEST_H_INCLUDED


namespace hext {

/// The test namespace contains all value tests.
namespace test {


/// Base class for all value tests. Value tests are used to validate attribute
/// values of nodes according to a Rule's definition.
class ValueTest
{
public:
  virtual ~ValueTest()
    {}

  /// Implementation must be provided in subclasses.
  virtual bool operator()(const char * /* dummy */) const = 0;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_VALUE_TEST_H_INCLUDED


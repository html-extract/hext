#ifndef HEXT_VALUE_TEST_H_INCLUDED
#define HEXT_VALUE_TEST_H_INCLUDED


namespace hext {


/// Base class for all ValueTests. ValueTests are used to validate attribute
/// values of nodes according to a Rule's definition.
class ValueTest
{
public:
  virtual ~ValueTest() {}

  /// Implementation must be provided in subclasses.
  virtual bool test(const char * /* dummy */) const = 0;
};


} // namespace hext


#endif // HEXT_VALUE_TEST_H_INCLUDED


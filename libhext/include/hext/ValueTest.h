#ifndef HEXT_VALUE_TEST_H_INCLUDED
#define HEXT_VALUE_TEST_H_INCLUDED


namespace hext {


/// Abstract base for every ValueTest.
/// ValueTests determine whether a string passes a certain test.
class ValueTest
{
public:
  /// Allow inheritance.
  virtual ~ValueTest() {}

  /// Implementation must be provided in subclasses.
  virtual bool test(const char * /* dummy */) const = 0;
};


} // namespace hext


#endif // HEXT_VALUE_TEST_H_INCLUDED


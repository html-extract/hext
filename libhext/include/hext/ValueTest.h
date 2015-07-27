#ifndef HEXT_VALUE_TEST_H_INCLUDED
#define HEXT_VALUE_TEST_H_INCLUDED

/// @file
///   Declares hext::ValueTest


namespace hext {


/// Abstract base for every ValueTest.
/// ValueTests determine whether a string passes a certain test.
class ValueTest
{
public:
  // Rule of five
  ValueTest() = default;
  ValueTest(const ValueTest&) = default;
  ValueTest(ValueTest&&) = default;
  ValueTest& operator=(const ValueTest&) = default;
  ValueTest& operator=(ValueTest&&) = default;

  /// Allow inheritance.
  virtual ~ValueTest() = default;

  /// Implementation must be provided in subclasses.
  virtual bool test(const char * /* dummy */) const = 0;
};


} // namespace hext


#endif // HEXT_VALUE_TEST_H_INCLUDED


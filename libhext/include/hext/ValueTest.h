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
  ValueTest() noexcept = default;
  ValueTest(const ValueTest&) noexcept = default;
  ValueTest(ValueTest&&) noexcept = default;
  ValueTest& operator=(const ValueTest&) noexcept = default;
  ValueTest& operator=(ValueTest&&) noexcept = default;

  /// Allow inheritance.
  virtual ~ValueTest() noexcept = default;

  /// Implementation must be provided in subclasses.
  virtual bool test(const char * /* dummy */) const = 0;
};


} // namespace hext


#endif // HEXT_VALUE_TEST_H_INCLUDED


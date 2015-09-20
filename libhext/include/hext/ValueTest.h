#ifndef HEXT_VALUE_TEST_H_INCLUDED
#define HEXT_VALUE_TEST_H_INCLUDED

/// @file
///   Declares hext::ValueTest

#include <memory>


namespace hext {


/// Abstract base for every ValueTest.
/// ValueTests determine whether a string passes a certain test.
///
/// Note: You probably don't want to inherit from this class directly, unless
///       you want to provide your own ValueTest::clone() method. If your
///       subclass has a copy constructor, you can extend from
///       hext::Cloneable<YourSubclass, hext::ValueTest> which provides a
///       generic clone method.
class ValueTest
{
public:
  // Rule of five
  ValueTest() = default;
  ValueTest(const ValueTest&) = default;
  ValueTest(ValueTest&&) = default;
  ValueTest& operator=(const ValueTest&) = default;
  ValueTest& operator=(ValueTest&&) = default;
  virtual ~ValueTest() = default;

  /// Clones derived object.
  virtual std::unique_ptr<ValueTest> clone() const = 0;

  /// Returns true if subject passes this ValueTest.
  virtual bool test(const char * /* dummy */) const = 0;
};


} // namespace hext


#endif // HEXT_VALUE_TEST_H_INCLUDED


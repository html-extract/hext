#ifndef HEXT_VALUE_TEST_H
#define HEXT_VALUE_TEST_H

#include <string>
#include <iostream>


namespace hext {


class ValueTest
{
public:
  virtual ~ValueTest();
  virtual bool test(const char * /* dummy */) const;
  virtual void print(std::ostream& /* dummy */ = std::cout) const;
};


} // namespace hext

#endif // HEXT_VALUE_TEST_H


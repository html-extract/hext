#ifndef HEXT_ATTR_TEST_H
#define HEXT_ATTR_TEST_H

#include <string>
#include <iostream>


namespace hext {


class AttrTest
{
public:
  virtual ~AttrTest();
  virtual bool test(const char * /* dummy */) const;
  virtual void print(std::ostream& /* dummy */ = std::cout) const;
};


} // namespace hext

#endif // HEXT_ATTR_TEST_H


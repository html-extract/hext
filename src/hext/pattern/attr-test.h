#ifndef HEXT_ATTR_TEST_H
#define HEXT_ATTR_TEST_H

#include <string>
#include <iostream>


namespace hext {


class attr_test
{
public:
  virtual ~attr_test();
  virtual bool test(const std::string& /* dummy */) const;
  virtual void print(std::ostream& /* dummy */ = std::cout) const;
};


} // namespace hext

#endif // HEXT_ATTR_TEST_H


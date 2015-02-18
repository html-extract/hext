#ifndef HEXT_LITERAL_TEST_H
#define HEXT_LITERAL_TEST_H

#include <string>
#include <iostream>

#include "hext/pattern/attr-test.h"


namespace hext {


class literal_test : public attr_test
{
public:
  explicit literal_test(std::string literal);
  bool test(const std::string& subject) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const std::string lit;
};


} // namespace hext


#endif // HEXT_LITERAL_TEST_H


#ifndef HEXT_LITERAL_TEST_H
#define HEXT_LITERAL_TEST_H

#include <string>
#include <iostream>

#include "hext/pattern/value-test.h"


namespace hext {


class LiteralTest : public ValueTest
{
public:
  explicit LiteralTest(std::string literal);
  bool test(const char * subject) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const std::string lit_;
};


} // namespace hext


#endif // HEXT_LITERAL_TEST_H


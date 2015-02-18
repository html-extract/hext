#ifndef HEXT_REGEX_TEST_H
#define HEXT_REGEX_TEST_H

#include <string>
#include <iostream>

#include <boost/regex.hpp>

#include "hext/pattern/attr-test.h"


namespace hext {


class regex_test : public attr_test
{
public:
  explicit regex_test(const std::string& regex);
  bool test(const char * subject) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const boost::regex rx;
};


} // namespace hext


#endif // HEXT_REGEX_TEST_H


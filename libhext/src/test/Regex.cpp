#include "hext/test/Regex.h"


namespace hext {
namespace test {


Regex::Regex(const boost::regex& regex)
: rx_(regex)
{
}

bool Regex::test(const char * subject) const
{
  return boost::regex_search(subject, this->rx_);
}


} // namespace test
} // namespace hext


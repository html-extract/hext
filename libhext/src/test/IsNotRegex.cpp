#include "hext/test/IsNotRegex.h"


namespace hext {
namespace test {


IsNotRegex::IsNotRegex(const boost::regex& regex)
: rx_(regex)
{
}

bool IsNotRegex::operator()(const char * subject) const
{
  return !boost::regex_search(subject, this->rx_);
}


} // namespace test
} // namespace hext


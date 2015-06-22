#include "hext/test/Regex.h"


namespace hext {
namespace test {


Regex::Regex(boost::regex regex)
: rx_(std::move(regex))
{
}

bool Regex::operator()(const char * subject) const
{
  return boost::regex_search(subject, this->rx_);
}


} // namespace test
} // namespace hext


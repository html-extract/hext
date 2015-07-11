#include "hext/test/Regex.h"

#include <utility>


namespace hext {
namespace test {


Regex::Regex(boost::regex regex)
: rx_(std::move(regex))
{
}

bool Regex::operator()(const char * subject) const
{
  if( !subject )
    return false;

  return boost::regex_search(subject, this->rx_);
}


} // namespace test
} // namespace hext


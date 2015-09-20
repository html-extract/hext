#include "hext/CasePipe.h"

#include <boost/algorithm/string.hpp>


namespace hext {


CasePipe::CasePipe(CasePipe::Option option)
: option_(option)
{
}

std::string CasePipe::transform(std::string str) const
{
  if( this->option_ & Option::ToLower )
    boost::algorithm::to_lower(str);
  else
    boost::algorithm::to_upper(str);

  return str;
}


} // namespace hext


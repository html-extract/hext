#include "hext/util.h"


namespace hext {
namespace util {


std::string escape_quotes(const std::string& str)
{
  std::string ret;
  ret.reserve(str.length());
  for(auto c : str)
  {
    if( c == '"' )
      ret.push_back('\\');
    ret.push_back(c);
  }

  return ret;
}


} // namespace util
} // namespace hext


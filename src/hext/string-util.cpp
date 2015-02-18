#include "hext/string-util.h"


namespace hext {


std::string trim_and_collapse_ws(std::string str)
{
  std::string::size_type i = 0;
  std::string::size_type c = 0;
  bool need_space = false;

  for(; c < str.size(); c++)
  {
    if( is_space(str[c]) )
    {
      if( i > 0 )
        need_space = true;
    }
    else
    {
      if( need_space )
      {
        str[i++] = ' ';
        need_space = false;
      }
      str[i++] = str[c];
    }
  }

  str.erase(i);
  return str;
}

bool is_space(char c)
{
  // The space characters, for the purposes of this specification,
  // are U+0020 SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C),
  // and "CR" (U+000D).
  switch( c )
  {
    case ' ':
    case '\t':
    case '\n':
    case '\f':
    case '\r':
      return true;
  }

  return false;
}


} // namespace hext


#include "hext/ParseHext.h"

#include "Parser.h"

#include <cstring>


namespace hext {


Rule ParseHext(const char * hext)
{
  return ParseHext(hext, std::strlen(hext));
}

Rule ParseHext(const char * hext, std::size_t size)
{
  Parser parser(hext, hext + size);
  return parser.parse();
}


} // namespace hext


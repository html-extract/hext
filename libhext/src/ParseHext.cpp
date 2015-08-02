#include "hext/ParseHext.h"

#include "Parser.h"

#include <cstring>
#include <utility>


namespace hext {


std::unique_ptr<Rule> ParseHext(const char * hext)
{
  return std::move(ParseHext(hext, std::strlen(hext)));
}

std::unique_ptr<Rule> ParseHext(const char * hext, std::size_t size)
{
  Parser parser(hext, hext + size);
  return std::move(parser.parse());
}


} // namespace hext


#ifndef HEXT_HEXT_H_INCLUDED
#define HEXT_HEXT_H_INCLUDED

#include "hext/parser.h"
#include "hext/result.h"
#include "hext/option.h"
#include "hext/rule.h"
#include "hext/html.h"

#include <vector>
#include <string>


namespace hext {


class HtmlExtract
{
public:
  explicit HtmlExtract(const std::string& hext);
  Result extract(const std::string& html, Option flags = Option::Default) const;

private:
  std::vector<Rule> rules_;
};


} // namespace hext


#endif // HEXT_HEXT_H_INCLUDED


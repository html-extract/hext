#ifndef HEXT_HEXT_H_INCLUDED
#define HEXT_HEXT_H_INCLUDED

#include "hext/Parser.h"
#include "hext/Result.h"
#include "hext/Option.h"
#include "hext/Rule.h"
#include "hext/Html.h"

#include <vector>
#include <string>


namespace hext {


class Hext
{
public:
  explicit Hext(const std::string& hext);
  Result extract(const std::string& html, Option flags = Option::Default) const;

private:
  std::vector<Rule> rules_;
};


} // namespace hext


#endif // HEXT_HEXT_H_INCLUDED


#ifndef HEXT_REGEX_MATCH_H
#define HEXT_REGEX_MATCH_H

#include <string>
#include <iostream>

#include <gumbo.h>
#include <boost/regex.hpp>

#include "hext/match-pattern.h"


namespace hext {


/// A regex_match is a match_pattern that checks whether an html-node has an
/// attribute called attr_name with a value that is matched by regex.
class regex_match : public match_pattern
{
public:
  regex_match(const std::string& attr_name, const std::string& regex);
  const GumboAttribute * matches(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const boost::regex rx;
};


} // namespace hext


#endif // HEXT_REGEX_MATCH_H


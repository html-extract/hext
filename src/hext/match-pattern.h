#ifndef HEXT_MATCH_PATTERN_H
#define HEXT_MATCH_PATTERN_H

#include <string>
#include <iostream>

#include <gumbo.h>


namespace hext {


/// match_pattern is the base class for all patterns that are used to check
/// whether an html-node is matched by a rule. Rules have match_patterns.
/// In its basic form a match_pattern checks whether an html-node has an
/// attribute called attr_name.
/// See also hext/regex-match.h and hext/literal-match.h
class match_pattern
{
public:
  explicit match_pattern(const std::string& attr_name);
  /// Return true if GumboNode has any attribute called attr_name
  virtual bool matches(const GumboNode * node) const;
  virtual void print(std::ostream& out = std::cout) const;
  virtual ~match_pattern();

protected:
  /// Get a GumboAttribute pointer to the node's attribute called attr_name.
  /// Returns nullptr if not found.
  const GumboAttribute * get_node_attr(const GumboNode * node) const;
  const std::string attr;
};


} // namespace hext


#endif // HEXT_MATCH_PATTERN_H


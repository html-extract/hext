#ifndef HEXT_ATTRIBUTE_MATCH_H
#define HEXT_ATTRIBUTE_MATCH_H

#include <string>
#include <iostream>

#include <gumbo.h>

#include "hext/pattern/match-pattern.h"


namespace hext {


/// An attribute_match is a match_pattern that checks whether an html-node has
/// any attribute called attr_name.
class attribute_match : public match_pattern
{
public:
  explicit attribute_match(const std::string& attr_name);
  virtual ~attribute_match() override;
  /// Returns std::pair<false, nullptr> if GumboNode does not have any
  /// attribute called attr_name
  virtual match_result matches(const GumboNode * node) const override;
  virtual void print(std::ostream& out = std::cout) const override;

protected:
  /// Get a GumboAttribute pointer to the node's attribute called attr_name.
  /// Returns nullptr if not found.
  const GumboAttribute * get_node_attr(const GumboNode * node) const;
  const std::string attr;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_MATCH_H


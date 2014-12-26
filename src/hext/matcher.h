#ifndef HEXT_MATCHER_H
#define HEXT_MATCHER_H

#include <cassert>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <queue>
#include <tuple>

#include <gumbo.h>

#include "hext/rule.h"
#include "hext/attribute.h"
#include "hext/match-tree.h"
#include "hext/make-unique.h"
#include "hext/builtin-captures.h"


namespace hext {


class matcher
{
public:
  class match_error : public std::runtime_error
  {
  public:
    explicit match_error(const char * msg);
  };

  explicit matcher(const char * path);

  std::unique_ptr<match_tree>
  capture_node(const rule * r, const GumboNode * node) const;

  match_tree::name_value_pair
  capture_attribute(const attribute * a, const GumboNode * node) const;

  bool node_matches_rule(const GumboNode * node, const rule * r) const;

  std::unique_ptr<match_tree> match(const rule * r) const;

  void match_node(const rule * r, const GumboNode * node, match_tree * m) const;

  void match_node_children(const rule * r, const GumboNode * node, match_tree * m) const;

  ~matcher();

private:
  matcher(const matcher&) = delete;
  matcher& operator=(const matcher&) = delete;

  GumboOutput * g_outp;
  std::string buffer;
};


} // namespace hext


#endif // HEXT_MATCHER_H


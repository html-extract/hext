#ifndef HEXT_RULE_H
#define HEXT_RULE_H

#include <string>
#include <vector>
#include <memory>

#include <gumbo.h>

#include "hext/make-unique.h"
#include "hext/attribute.h"


namespace hext {


class match_tree;

class rule
{
public:
  rule();

  void append_child(const rule& r, int level = 0);
  void append_attribute(attribute attr);

  std::vector<rule>::size_type children_size() const;
  std::string get_tag_name() const;
  void set_tag_name(std::string name);

  void match(const GumboNode * node, match_tree * m) const;

  std::unique_ptr<match_tree> capture(const GumboNode * node) const;

  void print(std::ostream& out = std::cout, int indent_level = 0) const;

private:
  bool matches(const GumboNode * node) const;

  void match_node_children(const GumboNode * node, match_tree * m) const;

  std::vector<rule> children;
  std::vector<attribute> attributes;

  std::string tag_name;
};  


} // namespace hext


#endif // HEXT_RULE_H


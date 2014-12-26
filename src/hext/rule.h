#ifndef HEXT_RULE_H
#define HEXT_RULE_H

#include <string>
#include <vector>
#include <memory>

#include <gumbo.h>

#include "hext/make-unique.h"
#include "hext/attribute.h"
#include "hext/match-tree.h"


namespace hext {


class rule
{
public:
  typedef std::vector<rule>::const_iterator const_child_iterator;
  typedef std::vector<rule>::iterator child_iterator;
  typedef std::vector<attribute>::const_iterator const_attribute_iterator;
  typedef std::vector<attribute>::iterator attribute_iterator;

  rule();

  const_child_iterator children_begin() const;
  const_child_iterator children_end() const;
  child_iterator children_begin();
  child_iterator children_end();
  std::vector<rule>::size_type children_size() const;

  const_attribute_iterator attributes_begin() const;
  const_attribute_iterator attributes_end() const;
  std::vector<attribute>::size_type attributes_size() const;

  void print(std::ostream& out = std::cout, int indent_level = 0) const;

  void append_child(rule r);
  void append_attribute(attribute attr);

  std::string get_tag_name() const;
  void set_tag_name(std::string name);

  void match_recursively(
    const GumboNode * node,
    match_tree * m
  ) const;

  void match_node_children(
    const GumboNode * node,
    match_tree * m
  ) const;

  bool matches(const GumboNode * node) const;

  std::unique_ptr<match_tree>
  capture(const GumboNode * node) const;

private:
  std::vector<rule> children;
  std::vector<attribute> attributes;

  std::string tag_name;
};  


} // namespace hext


#endif // HEXT_RULE_H


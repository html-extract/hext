#ifndef HEXT_RULE_H
#define HEXT_RULE_H

#include <string>
#include <vector>

#include "hext/attribute.h"


namespace hext {


class rule
{
public:
  typedef std::vector<rule>::const_iterator const_child_iterator;
  typedef std::vector<rule>::iterator child_iterator;
  typedef std::vector<attribute>::const_iterator const_attribute_iterator;
  typedef std::vector<attribute>::iterator attribute_iterator;

  rule()
  : children(),
    attributes(),
    tag_name("*"),
    direct_descendant(false),
    capture_limit(1)
  {
  }

  const_child_iterator children_begin() const
  {
    return this->children.cbegin();
  }

  const_child_iterator children_end() const
  {
    return this->children.cend();
  }

  child_iterator children_begin()
  {
    return this->children.begin();
  }

  child_iterator children_end()
  {
    return this->children.end();
  }

  std::vector<rule>::size_type children_size() const
  {
    return this->children.size();
  }

  const_attribute_iterator attributes_begin() const
  {
    return this->attributes.cbegin();
  }

  const_attribute_iterator attributes_end() const
  {
    return this->attributes.cend();
  }

  std::vector<attribute>::size_type attributes_size() const
  {
    return this->attributes.size();
  }

  void append_child(rule r)
  {
    this->children.push_back(r);
  }

  void append_attribute(attribute attr)
  {
    this->attributes.push_back(attr);
  }

  std::string get_tag_name() const
  {
    return this->tag_name;
  }

  bool get_is_direct_descendant() const
  {
    return this->direct_descendant;
  }

  unsigned int get_capture_limit()
  {
    return this->capture_limit;
  }

  void set_tag_name(std::string name)
  {
    this->tag_name = name;
  }

  void set_is_direct_descendant(bool is_direct_descendant)
  {
    this->direct_descendant = is_direct_descendant;
  }

  void set_capture_limit(unsigned int cap_limit)
  {
    this->capture_limit = cap_limit;
  }

private:
  std::vector<rule> children;
  std::vector<attribute> attributes;

  std::string tag_name;
  bool direct_descendant;
  unsigned int capture_limit;
};  


} // namespace hext


#endif // HEXT_RULE_H


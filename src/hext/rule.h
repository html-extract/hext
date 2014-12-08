#ifndef HEXT_RULE_H
#define HEXT_RULE_H

#include <string>
#include <vector>

#include "hext/attribute.h"


namespace hext {


class rule
{
public:
  rule()
  : children(),
    attributes(),
    tag_name("*"),
    direct_descendant(false)
  {
  }

  std::vector<rule>::const_iterator children_begin() const
  {
    return this->children.cbegin();
  }

  std::vector<rule>::const_iterator children_end() const
  {
    return this->children.cend();
  }

  std::vector<attribute>::const_iterator attributes_begin() const
  {
    return this->attributes.cbegin();
  }

  std::vector<attribute>::const_iterator attributes_end() const
  {
    return this->attributes.cend();
  }

  void append_attribute(attribute attr)
  {
    this->attributes.push_back(attr);
  }

  void append_child(rule r)
  {
    this->children.push_back(r);
  }

  std::string get_tag_name() const
  {
    return this->tag_name;
  }

  bool get_is_direct_descendant() const
  {
    return this->direct_descendant;
  }

  void set_tag_name(std::string name)
  {
    this->tag_name = name;
  }

  void set_is_direct_descendant(bool is_direct_descendant)
  {
    this->direct_descendant = is_direct_descendant;
  }

private:
  std::vector<rule> children;
  std::vector<attribute> attributes;

  std::string tag_name;
  bool direct_descendant;
};  


} // namespace hext


#endif // HEXT_RULE_H


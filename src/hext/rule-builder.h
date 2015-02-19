#ifndef HEXT_RULE_BUILDER_H
#define HEXT_RULE_BUILDER_H


#include <string>
#include <memory>
#include <vector>

#include "hext/rule.h"
#include "hext/rule-patterns.h"


namespace hext {


class rule_builder
{
public:
  rule_builder();
  ~rule_builder();
  rule build_and_reset();

  void set_tag_name(const std::string& tag);
  void set_direct_descendant(bool direct_desc);
  void set_closed(bool closed);
  void set_nth_child(unsigned int pos_within_parent);
  void append_match_pattern(std::unique_ptr<match_pattern> p);
  void append_capture_pattern(std::unique_ptr<capture_pattern> p);

private:
  std::string tag_name;
  bool is_direct_desc;
  bool is_closed;
  unsigned int nth_child;
  std::vector<std::unique_ptr<match_pattern>> mp;
  std::vector<std::unique_ptr<capture_pattern>> cp;
};


} // namespace hext


#endif // HEXT_RULE_BUILDER_H


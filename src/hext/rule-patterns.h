#ifndef HEXT_RULE_PATTERNS_H
#define HEXT_RULE_PATTERNS_H

#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

#include <gumbo.h>

#include "hext/make-unique.h"
#include "hext/match-tree.h"
#include "hext/pattern/match-pattern.h"
#include "hext/pattern/capture-pattern.h"


namespace hext {


/// Rule-patterns contain the patterns of a rule.
/// There are two types of patterns: match-patterns and capture-patterns.
class rule_patterns
{
public:
  rule_patterns(
    std::vector<std::unique_ptr<match_pattern>>&& match_patterns,
    std::vector<std::unique_ptr<capture_pattern>>&& capture_patterns
  );
  ~rule_patterns();
  rule_patterns(rule_patterns&&) = default;
  /// Apply all match patterns to node.
  /// Returns true if all match patterns match.
  bool matches(const GumboNode * node) const;
  /// Apply all match patterns to node.
  /// Returns true if all node-attributes were matched.
  bool matches_all_attributes(const GumboNode * node) const;
  /// Apply all capture patterns to node.
  /// Returns a new match_tree branch.
  std::unique_ptr<match_tree> capture(const GumboNode * node) const;
  void print(std::ostream& out = std::cout) const;

private:
  std::vector<std::unique_ptr<match_pattern>> matchp;
  std::vector<std::unique_ptr<capture_pattern>> capturep;
};


} // namespace hext


#endif // HEXT_RULE_PATTERNS_H


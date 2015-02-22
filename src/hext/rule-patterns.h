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


/// RulePatterns contain the patterns of a rule.
/// There are two types of patterns: MatchPatterns and CapturePatterns.
class RulePatterns
{
public:
  RulePatterns(
    std::vector<std::unique_ptr<MatchPattern>>&& match_patterns,
    std::vector<std::unique_ptr<CapturePattern>>&& capture_patterns
  );
  ~RulePatterns();
  RulePatterns(RulePatterns&&) = default;
  /// Apply all MatchPatterns to node.
  /// Returns true if all MatchPatterns match.
  bool matches(const GumboNode * node) const;
  /// Apply all MatchPatterns to node.
  /// Returns true if all node-attributes were matched.
  bool matches_all_attributes(const GumboNode * node) const;
  /// Apply all capture patterns to node.
  /// Returns a new MatchTree branch.
  std::unique_ptr<MatchTree> capture(const GumboNode * node) const;
  void print(std::ostream& out = std::cout) const;

private:
  std::vector<std::unique_ptr<MatchPattern>> matchp;
  std::vector<std::unique_ptr<CapturePattern>> capturep;
};


} // namespace hext


#endif // HEXT_RULE_PATTERNS_H


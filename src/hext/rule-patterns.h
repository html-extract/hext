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
/// RulePatterns were created to lessen the amount of code in Rule.
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
  /// Return true if all MatchPatterns match.
  bool matches(const GumboNode * node) const;

  /// Apply all MatchPatterns to node.
  /// Return true if all MatchPatterns match and each node-attribute was
  /// matched with a MatchPattern ("closed Rule").
  bool matches_all_attributes(const GumboNode * node) const;

  /// Apply all capture patterns to node.
  /// Return a new MatchTree branch containing name-value-pair.
  std::unique_ptr<MatchTree> capture(const GumboNode * node) const;

  void print(std::ostream& out = std::cout) const;

private:
  std::vector<std::unique_ptr<MatchPattern>> matchp_;
  std::vector<std::unique_ptr<CapturePattern>> capturep_;
};


} // namespace hext


#endif // HEXT_RULE_PATTERNS_H


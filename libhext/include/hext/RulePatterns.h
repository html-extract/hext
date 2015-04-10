#ifndef HEXT_RULE_PATTERNS_H_INCLUDED
#define HEXT_RULE_PATTERNS_H_INCLUDED

#include "hext/MakeUnique.h"
#include "hext/pattern/MatchPattern.h"
#include "hext/pattern/CapturePattern.h"
#include "hext/Result.h"

#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

#include <gumbo.h>


namespace hext {


/// RulePatterns contain the patterns of a rule.
/// RulePatterns was created to lessen the amount of code in Rule.
/// There are two types of patterns: MatchPatterns and CapturePatterns.
class RulePatterns
{
public:
  RulePatterns(
    std::vector<std::unique_ptr<MatchPattern>>&& match_patterns,
    std::vector<std::unique_ptr<CapturePattern>>&& capture_patterns
  );
  RulePatterns(RulePatterns&&) = default;

  /// Apply all MatchPatterns to node.
  /// Return true if all MatchPatterns match.
  bool matches(const GumboNode * node) const;

  /// Apply all capture patterns to node. Return all captured string pairs.
  std::vector<ResultPair> capture(const GumboNode * node) const;

private:
  std::vector<std::unique_ptr<MatchPattern>> match_patterns_;
  std::vector<std::unique_ptr<CapturePattern>> capture_patterns_;
};


} // namespace hext


#endif // HEXT_RULE_PATTERNS_H_INCLUDED


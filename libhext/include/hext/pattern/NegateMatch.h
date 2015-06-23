#ifndef HEXT_PATTERN_NEGATE_MATCH_H_INCLUDED
#define HEXT_PATTERN_NEGATE_MATCH_H_INCLUDED

#include "hext/pattern/MatchPattern.h"

#include <cassert>
#include <memory>
#include <utility>
#include <vector>

#include <gumbo.h>


namespace hext {


/// A NegateMatch is a MatchPattern that matches if all contained MatchPatterns
/// return false for a given GumboNode.
class NegateMatch : public MatchPattern
{
public:
  explicit NegateMatch(
    std::vector<std::unique_ptr<MatchPattern>>&& match_patterns =
      std::vector<std::unique_ptr<MatchPattern>>()
  );

  void take_match(std::unique_ptr<MatchPattern>&& pattern);

  // Return true if all contained MatchPatterns return false.
  // Return true on empty MatchPatterns.
  bool matches(const GumboNode * node) const final;

private:
  std::vector<std::unique_ptr<MatchPattern>> match_patterns_;
};


} // namespace hext


#endif // HEXT_PATTERN_NEGATE_MATCH_H_INCLUDED


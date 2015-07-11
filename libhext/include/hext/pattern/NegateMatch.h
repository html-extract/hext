#ifndef HEXT_PATTERN_NEGATE_MATCH_H_INCLUDED
#define HEXT_PATTERN_NEGATE_MATCH_H_INCLUDED

#include "hext/pattern/Match.h"

#include <memory>
#include <vector>

#include <gumbo.h>


namespace hext {


/// Match if all contained Matches return false for a given GumboNode.
class NegateMatch : public Match
{
public:
  explicit NegateMatch(
    std::vector<std::unique_ptr<Match>>&& v_matches =
      std::vector<std::unique_ptr<Match>>()
  );

  void take_match(std::unique_ptr<Match>&& match);

  // Return true if all contained Matches return false.
  // Return true on empty Matches.
  bool matches(const GumboNode * node) const final;

private:
  std::vector<std::unique_ptr<Match>> matches_;
};


} // namespace hext


#endif // HEXT_PATTERN_NEGATE_MATCH_H_INCLUDED


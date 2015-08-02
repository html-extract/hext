#ifndef HEXT_MATCHCONTEXT_H_INCLUDED
#define HEXT_MATCHCONTEXT_H_INCLUDED

#include <utility>
#include <vector>

#include <boost/optional.hpp>
#include <gumbo.h>


namespace hext {


class Rule;


class MatchContext
{
public:
  typedef std::vector<std::pair<const Rule *, const GumboNode *>> match_group;

  MatchContext(const Rule * rule,
               const GumboNode * node) noexcept;

  /// Returns the next match_group.
  /// Returns empty if there are no more matches.
  boost::optional<match_group> match_next();

private:
  const Rule * find_mandatory_rule(const Rule * begin, const Rule * end) const;

  const GumboNode * find_match(const GumboNode * begin,
                               const GumboNode * end,
                               const Rule * rule) const;

  void match_to_node(match_group& mg,
                     const Rule * rule,
                     const Rule * stop_rule,
                     const GumboNode * stop_node);

  const Rule * const rule_;
  const GumboNode * node_;
};


} // namespace hext


#endif // HEXT_MATCHCONTEXT_H_INCLUDED


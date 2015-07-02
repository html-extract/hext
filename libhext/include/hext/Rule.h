#ifndef HEXT_RULE_H_INCLUDED
#define HEXT_RULE_H_INCLUDED

#include "hext/Result.h"
#include "hext/ResultTree.h"
#include "hext/MakeUnique.h"
#include "hext/pattern/MatchPattern.h"
#include "hext/pattern/CapturePattern.h"

#include <cstddef>
#include <memory>
#include <vector>

#include <gumbo.h>


namespace hext {


/// A Rule defines how to match and capture html-nodes. It can be applied to a
/// GumboNode tree, where it recursively tries to find matches. Once a match is
/// found, the Rule appends a new branch to a ResultTree containing the captured
/// values of an html-node.
///
/// A Rule is a tree: A Rule can have multiple Rule children.
class Rule
{
public:
  /// Construct a Rule.
  ///
  /// \param tag
  ///    The tag-name of the rule, as parsed by gumbo. Matches if the node's tag
  ///    is the same. Set to GUMBO_TAG_UNKNOWN if any tag may match.
  ///
  /// \param optional
  ///    A subtree matches only if all mandatory rules were matched. Optional
  ///    rules on the other hand are ignored if not found.
  explicit Rule(GumboTag tag = GUMBO_TAG_UNKNOWN, bool optional = false);
  ~Rule();
  Rule(Rule&&);
  Rule& operator=(Rule&&);

  /// Append a child-rule after the last element at the given tree depth.
  Rule& take_child(Rule&& r, std::size_t insert_at_depth = 0);

  /// Take a MatchPattern.
  Rule& take_match(std::unique_ptr<MatchPattern>&& pattern);

  /// Emplace a MatchPattern.
  template<typename MatchPatternType, typename... Args>
  Rule& add_match(Args&&... arg)
  {
    return this->take_match(
      MakeUnique<MatchPatternType>(std::forward<Args>(arg)...)
    );
  }

  /// Take a CapturePattern.
  Rule& take_capture(std::unique_ptr<CapturePattern>&& pattern);

  /// Emplace a CapturePattern.
  template<typename CapturePatternType, typename... Args>
  Rule& add_capture(Args&&... arg)
  {
    return this->take_capture(
      MakeUnique<CapturePatternType>(std::forward<Args>(arg)...)
    );
  }

  /// Return the type of html-tag this rule matches, as parsed by gumbo.
  /// Return GUMBO_TAG_UNKNOWN if this rule matches any tag.
  GumboTag get_tag() const;

  /// Set the type of html-tag this rule matches, as parsed by gumbo. Set to
  /// GUMBO_TAG_UNKNOWN if this rule should match any tag.
  Rule& set_tag(GumboTag tag);

  /// Return true if this rule is optional, i.e. if a match does not have to be
  /// found.
  bool is_optional() const;

  /// Set whether this rule is optional, i.e. if a match has to be found.
  Rule& set_optional(bool optional);

  /// Recursively try to find and capture matches.
  std::unique_ptr<ResultTree> extract(const GumboNode * node) const;

  /// Check if this Rule matches a single GumboNode.
  bool matches(const GumboNode * node) const;

  /// Return the result of applying all CapturePatterns to node.
  std::vector<ResultPair> capture(const GumboNode * node) const;

private:
  Rule(const Rule&) = delete;
  Rule& operator=(const Rule&) = delete;

  struct Impl;
  std::unique_ptr<Impl> impl_;
};


} // namespace hext


#endif // HEXT_RULE_H_INCLUDED


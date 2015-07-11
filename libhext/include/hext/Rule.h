#ifndef HEXT_RULE_H_INCLUDED
#define HEXT_RULE_H_INCLUDED

#include "hext/HtmlTag.h"
#include "hext/Result.h"
#include "hext/ResultTree.h"
#include "hext/MakeUnique.h"
#include "hext/Match.h"
#include "hext/Capture.h"

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
  ///    The tag-name of the rule. Matches if the node's tag is the same. Set to
  ///    HtmlTag::ANY if any tag may match.
  ///
  /// \param optional
  ///    A subtree matches only if all mandatory rules were matched. Optional
  ///    rules on the other hand are ignored if not found.
  ///
  /// \param path
  ///    Paths do not modify the ResultTree (i.e. no branching for matches, no
  ///    capturing of values).
  explicit
  Rule(HtmlTag tag = HtmlTag::ANY, bool optional = false, bool path = false);
  ~Rule();
  Rule(Rule&&);
  Rule& operator=(Rule&&);

  /// Append a child-rule after the last element at the given tree depth.
  Rule& take_child(Rule&& r, std::size_t insert_at_depth = 0);

  /// Take a Match.
  Rule& take_match(std::unique_ptr<Match>&& match);

  /// Emplace a Match.
  template<typename MatchType, typename... Args>
  Rule& add_match(Args&&... arg)
  {
    return this->take_match(
      MakeUnique<MatchType>(std::forward<Args>(arg)...)
    );
  }

  /// Take a Capture.
  Rule& take_capture(std::unique_ptr<Capture>&& cap);

  /// Emplace a Capture.
  template<typename CaptureType, typename... Args>
  Rule& add_capture(Args&&... arg)
  {
    return this->take_capture(
      MakeUnique<CaptureType>(std::forward<Args>(arg)...)
    );
  }

  /// Return the type of html-tag this rule matches.
  HtmlTag get_tag() const;

  /// Set the type of html-tag this rule matches.
  Rule& set_tag(HtmlTag tag);

  /// Return true if this rule is optional, i.e. if a match does not have to be
  /// found.
  bool is_optional() const;

  /// Set whether this rule is optional, i.e. if a match has to be found.
  Rule& set_optional(bool optional);

  /// Recursively try to find and capture matches.
  std::unique_ptr<ResultTree> extract(const GumboNode * node) const;

  /// Check if this Rule matches a single GumboNode.
  bool matches(const GumboNode * node) const;

  /// Return the result of applying all Captures to node.
  std::vector<ResultPair> capture(const GumboNode * node) const;

  /// Return if this Rule is a path. Paths do not modify the ResultTree (i.e.
  /// no branching for matches, no capturing of values).
  bool is_path() const;

  /// Set whether this Rule is a path. Paths do not modify the ResultTree (i.e.
  /// no branching for matches, no capturing of values).
  Rule& set_path(bool path);

private:
  Rule(const Rule&) = delete;
  Rule& operator=(const Rule&) = delete;

  struct Impl;
  std::unique_ptr<Impl> impl_;
};


} // namespace hext


#endif // HEXT_RULE_H_INCLUDED


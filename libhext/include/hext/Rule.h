#ifndef HEXT_RULE_H_INCLUDED
#define HEXT_RULE_H_INCLUDED

/// @file
///   Declares hext::Rule

#include "hext/HtmlTag.h"
#include "hext/Result.h"
#include "hext/ResultTree.h"
#include "hext/Match.h"
#include "hext/Capture.h"

#include <cstddef>
#include <memory>
#include <vector>

#include <gumbo.h>


namespace hext {


/// Extracts values from HTML.
///
/// A Rule is a tree: A Rule can have multiple Rule children.
///
/// A Rule defines how to match and capture HTML nodes. It can be applied to a
/// GumboNode tree, where it recursively tries to find matches. Once a match is
/// found, the Rule appends a new branch to a ResultTree containing the captured
/// values of an HTML node and then continues matching its own children down the
/// HTML tree.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   // create a rule that matches anchor elements, ..
///   Rule anchor(HtmlTag::A);
///   // .. which must have an attribute called "href"
///   anchor.add_match<AttributeMatch>("href")
///         // capture attribute href and save it as "link"
///         .add_capture<AttributeCapture>("href", "link");
///
///   {
///     // create a rule that matches image elements
///     Rule img(HtmlTag::IMG);
///     // capture attribute src and save it as "img"
///     img.add_capture<AttributeCapture>("src", "img");
///     // append the image-rule to the anchor-rule
///     anchor.take_child(std::move(img));
///   }
///
///   // anchor is now equivalent to the following hext:
///   // <a href={link}><img src={img}/></a>
///
///   Html html(
///     "<html><body>"
///       "<div><a href='/bob'>  <img src='bob.jpg'/>  </a></div>"
///       "<div><a href='/alice'><img src='alice.jpg'/></a></div>"
///       "<div><a href='/carol'><img src='carol.jpg'/></a></div>"
///     "</body></html>");
///
///   std::unique_ptr<ResultTree> rt = anchor.extract(html.root());
///
///   hext::Result result = rt->flatten();
///   // result will be equivalent to this:
///   // vector{
///   //   map{
///   //     {"link", "/bob"}
///   //     {"img", "bob.jpg"}
///   //   },
///   //   map{
///   //     {"link", "/alice"}
///   //     {"img", "alice.jpg"}
///   //   },
///   //   map{
///   //     {"link", "/carol"}
///   //     {"img", "carol.jpg"}
///   //   },
///   // }
/// ~~~~~~~~~~~~~
class Rule
{
public:
  /// Constructs a Rule.
  ///
  /// @param      tag:  The HtmlTag that this rule matches.
  ///                   Default: Match any tag.
  /// @param optional:  A subtree matches only if all mandatory rules were
  ///                   matched. Optional rules on the other hand are ignored
  ///                   if not found.
  ///                   Default: Rule is mandatory.
  /// @param     path:  Paths do not modify the ResultTree (i.e. no branching
  ///                   for matches, no capturing of values).
  ///                   Default: Rule is not a path.
  explicit Rule(HtmlTag   tag = HtmlTag::ANY,
                bool optional = false,
                bool     path = false);

  ~Rule() noexcept;
  Rule(Rule&&) noexcept;
  Rule& operator=(Rule&&) noexcept;

  /// Appends a Rule after the last element at the given tree depth.
  ///
  /// @param               r:  The rule to append.
  /// @param insert_at_depth:  The depth at which to append the rule.
  ///                          Default: Append immediately.
  /// @returns                 A reference for this Rule to enable method
  ///                          chaining.
  Rule& take_child(Rule&& r, std::size_t insert_at_depth = 0);

  /// Appends a Match.
  ///
  /// @param match:  The Match to append.
  /// @returns       A reference for this Rule to enable method chaining.
  Rule& take_match(std::unique_ptr<Match>&& match);

  /// Emplaces a Match.
  /// Forwards arguments to std::make_unique.
  ///
  /// @returns  A reference for this Rule to enable method chaining.
  template<typename MatchType, typename... Args>
  Rule& add_match(Args&&... arg)
  {
    return this->take_match(
        std::make_unique<MatchType>(std::forward<Args>(arg)...)
    );
  }

  /// Appends a Capture.
  ///
  /// @param cap:  The Capture to append.
  /// @returns     A reference for this Rule to enable method chaining.
  Rule& take_capture(std::unique_ptr<Capture>&& cap);

  /// Emplaces a Capture.
  /// Forwards arguments to std::make_unique.
  ///
  /// @returns  A reference for this Rule to enable method chaining.
  template<typename CaptureType, typename... Args>
  Rule& add_capture(Args&&... arg)
  {
    return this->take_capture(
        std::make_unique<CaptureType>(std::forward<Args>(arg)...)
    );
  }

  /// Returns the HtmlTag this rule matches.
  HtmlTag get_tag() const noexcept;

  /// Sets the HtmlTag this rule matches.
  ///
  /// @returns  A reference for this Rule to enable method chaining.
  Rule& set_tag(HtmlTag tag) noexcept;

  /// Returns true if this rule is optional, i.e. if a match does not have to
  /// be found.
  bool is_optional() const noexcept;

  /// Sets whether this rule is optional, i.e. if a match has to be found.
  ///
  /// @returns  A reference for this Rule to enable method chaining.
  Rule& set_optional(bool optional) noexcept;

  /// Extracts values from an HTML tree recursively.
  ///
  /// @returns  A ResultTree containing the captured values.
  std::unique_ptr<ResultTree> extract(const GumboNode * node) const;

  /// Returns true if this Rule matches node.
  ///
  /// @param node:  A GumboNode that is to be matched.
  bool matches(const GumboNode * node) const;

  /// Returns the result of applying every Capture to node.
  ///
  /// @param node:  A GumboNode that is to be captured.
  std::vector<ResultPair> capture(const GumboNode * node) const;

  /// Returns true if this Rule is a path.
  bool is_path() const noexcept;

  /// Sets whether this Rule is a path.
  ///
  /// @returns  A reference for this Rule to enable method chaining.
  Rule& set_path(bool path) noexcept;

private:
  Rule(const Rule&) = delete;
  Rule& operator=(const Rule&) = delete;

  struct Impl;
  std::unique_ptr<Impl> impl_;
};


} // namespace hext


#endif // HEXT_RULE_H_INCLUDED


#ifndef HEXT_NTHCHILD_MATCH_H_INCLUDED
#define HEXT_NTHCHILD_MATCH_H_INCLUDED

#include "hext/Match.h"
#include "hext/HtmlTag.h"

#include <utility>

#include <gumbo.h>


namespace hext {


/// Matches HTML nodes having a certain position within their parent HTML element.
///
/// The intent is to mimic the following CSS pseudo-classes:
///   nth-child,   nth-of-type, nth-last-of-type, first-of-type, last-of-type,
///   first-child, last-child,  nth-last-child,   nth-last-of-type
///
/// See https://developer.mozilla.org/en-US/docs/Web/CSS/%3Anth-child for a
/// detailed explanation.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   // Assume first, second, third are children of the following <ul> element:
///   // <ul><li>1</li><li>2</li><li>3</li></ul>
///   const GumboNode * first  = ...;
///   const GumboNode * second = ...;
///   const GumboNode * third  = ...;
///
///   NthChildMatch m_even(2, 0); // :nth-child(2n)
///   NthChildMatch m_odd (2, 1); // :nth-child(2n+1)
///
///   assert(!m_even.matches(first))
///   assert( m_even.matches(second))
///   assert(!m_even.matches(third))
///
///   assert( m_odd.matches(first))
///   assert(!m_odd.matches(second))
///   assert( m_odd.matches(third))
/// ~~~~~~~~~~~~~
///
/// @par last-of-type Example:
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~
///   // Assume first, second, third are children of the following <a> element:
///   // <a>
///   //   <b>1</b>
///   //   <u>2</u>
///   //   <b>3</b>
///   // </a>
///   const GumboNode * first  = ...;
///   const GumboNode * second = ...;
///   const GumboNode * third  = ...;
///
///   NthChildMatch m_last_b(0, 1, NthChildMatch::Back, HtmlTag::B);
///   NthChildMatch m_last_u(0, 1, NthChildMatch::Back, HtmlTag::U);
///
///   assert(!m_last_b.matches(first))
///   assert(!m_last_b.matches(second))
///   assert( m_last_b.matches(third))
///
///   assert(!m_last_u.matches(first))
///   assert( m_last_u.matches(second))
///   assert(!m_last_u.matches(third))
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~
class NthChildMatch : public Match
{
public:
  /// When determining the node's position, either count preceding siblings or
  /// following siblings.
  enum OffsetOf
  {
    /// Count preceding siblings.
    Front = 0,
    /// Count following siblings.
    Back
  };

  /// Constructs an NthChildMatch with the pattern <step * n + shift>.
  ///
  /// @param      step:  The step of the pattern.
  /// @param     shift:  The shift of the pattern.
  /// @param offset_of:  Whether the node's position should be determined by
  ///                    counting preceding siblings or following siblings.
  ///                    Default: Count preceding siblings.
  /// @param count_tag:  If given any value other than HtmlTag::ANY, only count
  ///                    siblings having this HtmlTag, when determining the
  ///                    node's position.
  ///                    Default: Count any HTML element.
  NthChildMatch(
    int step,
    int shift,
    OffsetOf offset_of = OffsetOf::Front,
    HtmlTag count_tag = HtmlTag::ANY
  );

  /// Construct an NthChildMatch with step and shift given as std::pair.
  /// Constructs an NthChildMatch with the pattern <step * n + shift>, where
  /// step and shift is given as a std::pair.
  ///
  /// @param step_and_shift:  The step and shift of the pattern.
  /// @param      offset_of:  Whether the node's position should be determined by
  ///                         counting preceding siblings or following siblings.
  ///                         Default: Count preceding siblings.
  /// @param      count_tag:  If given any value other than HtmlTag::ANY, only count
  ///                         siblings having this HtmlTag, when determining the
  ///                         node's position.
  ///                         Default: Count any HTML element.
  explicit NthChildMatch(
    std::pair<int, int> step_and_shift,
    OffsetOf offset_of = OffsetOf::Front,
    HtmlTag count_tag = HtmlTag::ANY
  );

  /// Returns true if HTML node matches pattern <step * n + shift>.
  ///
  /// @param node:  A pointer to a GumboNode.
  bool matches(const GumboNode * node) const final;

private:
  /// Count preceding siblings of an HTML node.
  ///
  /// @param      node:  A pointer to a GumboNode.
  /// @param count_tag:  If given any value other than HtmlTag::ANY, only count
  ///                    siblings having this HtmlTag.
  int count_preceding_siblings(
    const GumboNode * node,
    HtmlTag count_tag
  ) const;

  /// Count following siblings of an HTML node.
  ///
  /// @param      node:  A pointer to a GumboNode.
  /// @param count_tag:  If given any value other than HtmlTag::ANY, only count
  ///                    siblings having this HtmlTag.
  int count_following_siblings(
    const GumboNode * node,
    HtmlTag count_tag
  ) const;

  /// The step in the pattern <step * n + shift>
  int step_;

  /// The shift in the pattern <step * n + shift>
  int shift_;

  /// Whether to count preceding or following siblings when determining a node's
  /// position within its parent.
  OffsetOf offset_of_;

  /// When counting siblings, only count siblings that match this HtmlTag.
  HtmlTag count_tag_;
};


} // namespace hext


#endif // HEXT_NTHCHILD_MATCH_H_INCLUDED


#ifndef HEXT_HEXT_H_INCLUDED
#define HEXT_HEXT_H_INCLUDED

#include "hext/Parser.h"
#include "hext/Result.h"
#include "hext/ResultTree.h"
#include "hext/Option.h"
#include "hext/Rule.h"
#include "hext/Html.h"

#include <vector>
#include <string>
#include <utility>
#include <algorithm>


/// The hext namespace is the top level namespace for everything in libhext.
namespace hext {


/// Hext takes a string containing hext rule definitions. Once constructed, the
/// rules can be applied to html by calling Hext::extract, which returns a
/// Result containing all captured values.
///
/// Result flattening:
/// ----------------------------------------------------------------------------
///   Every top level rule creates its own hext::Result (std::vector) containing
///   instances of hext::ResultMap (std::multimap), which contain the captured
///   values.
///   Since we want to return a single hext::Result from Hext::extract, the
///   individual results need to be merged into one. The simple way is to put
///   all multimaps into a single vector. A better way is to interleave the
///   results. Consider the following html:
///   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///     <table>
///       <tr><td><a href="/article/1">How foo became bar</a></td></tr>
///       <tr><td>Comments: <span>42</span></td></tr>
///
///       <tr><td><a href="/article/2">Foo? Why not bar?</a></td></tr>
///       <tr><td>Comments: <span>23</span></td></tr>
///
///       <tr><td><a href="/article/3">10 reasons why bar is foo</a></td></tr>
///       <tr><td>Comments: <span>1</span></td></tr>
///     </table>
///   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///
///   And the following hext:
///   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///     <tr>                            # will produce Result#1
///       <td>
///         <a @text={title}>
///     <tr>                            # will produce Result#2
///       <td>
///         <span @text={comment_cnt}>
///   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///
///   Producing the following Results:
///   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///     Result#1: [{"title": "How foo became bar"},
///                {"title": "Foo? Why not bar?"},
///                {"title": "10 reasons why bar is foo"}]
///     Result#2: [{"comment_cnt": "42"},
///                {"comment_cnt": "23"},
///                {"comment_cnt": "1"}]
///   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///
///   Now the indvidual results have to be merged into a single hext::Result.
///   Naively appending Result#2 to Result#1 isn't useful in this case - A
///   favorable approach is to interleave the results in a way that reflects the
///   hext rule definitions. This behaviour is enabled by setting
///   Option::InterleaveResults (default on), which produces the following
///   hext::Result:
///   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///     [{"title": "How foo became bar", "comment_cnt": "42},
///      {"title": "Foo? Why not bar?", "comment_cnt": "23"},
///      {"title": "10 Reasons why bar is foo", "comment_cnt": "1"}]
///   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Hext
{
public:
  /// Construct Hext. Throws ParseError if given hext is invalid.
  ///
  /// \param hext
  ///     A string containing hext rule definitions.
  /// \param flags
  ///     Options.
  explicit Hext(const std::string& hext, Option flags = DefaultOption);

  /// Extract values from a string containing html.
  /// Return a hext::Result containing captured values.
  Result extract(const std::string& html) const;

  /// Extract values from a hext::Html.
  /// Return a hext::Result containing captured values.
  Result extract(const Html& html) const;

private:
  /// A vector of top-level rules.
  std::vector<Rule> rules_;

  /// Options.
  const Option flags_;
};


} // namespace hext


#endif // HEXT_HEXT_H_INCLUDED


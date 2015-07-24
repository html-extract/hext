#ifndef HEXT_STRING_UTIL_H_INCLUDED
#define HEXT_STRING_UTIL_H_INCLUDED

#include <cassert>
#include <cstdlib>
#include <string>
#include <utility>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <iostream>
#include <iomanip>

#include <boost/tokenizer.hpp>


namespace hext {


/// Removes whitespace from beginning and end and collapses multiple whitespace
/// to a single space, as is expected when extracting text from html. See
/// http://www.w3.org/TR/html5/infrastructure.html#strip-and-collapse-whitespace
///
/// @par Example:
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// "   Like\na Rolling\n\tStone  "
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// becomes
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// "Like a Rolling Stone"
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::string TrimAndCollapseWs(std::string str);


/// Returns true if given character is a space character according to the HTML
/// spec. std::isspace is not suitable, because it is locale aware.
/// See http://www.w3.org/TR/html5/infrastructure.html#space-character
bool IsSpace(char c) noexcept;


/// Returns a visual representation for every char, including control
/// characters like the nullbyte.
std::string CharName(char c);


/// Convenience typedefs for CharPosition().
typedef std::iterator_traits<const char *>::difference_type CharPosType;
typedef std::pair<CharPosType, CharPosType> CharPosPair;


/// Returns a pair<line_offset, character_offset> for the position of c after
/// begin. Numbering is zero-based.
///
/// @param begin:  The beginning of the overall string.
/// @param     c:  The character for which to calculate the position.
CharPosPair CharPosition(const char * begin, const char * c) noexcept;


/// Returns the width of number when printed as decimal.
int DecimalWidth(std::size_t number) noexcept;


/// Returns true if subject contains word. Word boundaries are the beginning and
/// end of subject, and spaces.
bool ContainsWord(const std::string& subject, const std::string& word) noexcept;


/// Prints begin to end into out, prepending a line number, a colon and a space
/// for each line.
///
/// @par Example:
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// An SQL query goes into a bar,
/// walks up to two tables and asks,
/// Can I join you?
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// becomes
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// 1: An SQL query goes into a bar,
/// 2: walks up to two tables and asks,
/// 3: Can I join you?
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PrintNumberedLines(const char *  begin,
                        const char *  end,
                        std::ostream& out);


} // namespace hext


#endif // HEXT_STRING_UTIL_H_INCLUDED


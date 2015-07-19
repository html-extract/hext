#ifndef HEXT_SYNTAX_ERROR_H_INCLUDED
#define HEXT_SYNTAX_ERROR_H_INCLUDED

#include <stdexcept>
#include <string>


namespace hext {


/// The exception that is thrown when parsing invalid hext.
/// SyntaxErrror.what() will contain a detailed error message.
class SyntaxError : public std::runtime_error
{
public:
  explicit SyntaxError(const std::string& msg);
};


} // namespace hext


#endif // HEXT_SYNTAX_ERROR_H_INCLUDED


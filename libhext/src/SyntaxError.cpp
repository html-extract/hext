#include "hext/SyntaxError.h"


namespace hext {


SyntaxError::SyntaxError(const std::string& msg)
: std::runtime_error(msg)
{
}


} // namespace hext


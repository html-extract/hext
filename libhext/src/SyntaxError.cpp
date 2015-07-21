#include "hext/SyntaxError.h"


namespace hext {


SyntaxError::SyntaxError(const std::string& msg) noexcept
: std::runtime_error(msg)  // noexcept
{
}


} // namespace hext


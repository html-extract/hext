#include "htmlext/ErrorOutput.h"


namespace htmlext {


ErrorOutput::ErrorOutput(const char * error_source, std::ostream& out) noexcept
: out_(out)                      // noexcept
, source_(error_source)          // noexcept
, isatty_(isatty(STDERR_FILENO)) // noexcept
{
}

void
ErrorOutput::print(const std::string& title, const std::string& contents) const
{
  this->out_ << ( this->isatty_ ? ErrorOutput::esc_red_ : "" )
             << this->source_ << ": "
             << title << ": "
             << ( this->isatty_ ? ErrorOutput::esc_reset_ : "" )
             << contents << "\n";
}


} // namespace htmlext


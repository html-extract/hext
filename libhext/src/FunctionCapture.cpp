#include "hext/FunctionCapture.h"

#include <cassert>
#include <utility>


namespace hext {


FunctionCapture::FunctionCapture(
  CaptureFunction func,
  std::string result_name,
  boost::optional<boost::regex> filter
)
: func_(std::move(func))         // noexcept
, name_(std::move(result_name))  // noexcept
, filter_(std::move(filter))     // boost::optional: noexcept >=1.56,
                                 // boost::regex:    not noexcept
{
}

boost::optional<ResultPair>
FunctionCapture::capture(const GumboNode * node) const
{
  assert(this->func_);
  if( !this->func_ )
    return {};

  auto str = this->func_(node);
  if( this->filter_ )
  {
    boost::match_results<std::string::iterator> mr;
    if( boost::regex_search(str.begin(), str.end(), mr, this->filter_.get()) )
    {
      // If there are no parentheses contained within the regex, return whole
      // regex capture (mr[0]), if there are, then return the first one.
      return ResultPair(
        this->name_,
        mr.size() > 1 ? mr[1] : mr[0]
      );
    }

    return {};
  }

  return ResultPair(this->name_, str);
}


} // namespace hext


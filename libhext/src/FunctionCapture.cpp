#include "hext/FunctionCapture.h"

#include <cassert>
#include <utility>


namespace hext {


FunctionCapture::FunctionCapture(
  CaptureFunction func,
  std::string result_name,
  boost::optional<boost::regex> regex
)
: func_(func)
, name_(std::move(result_name))
, rx_(std::move(regex))
{
}

boost::optional<ResultPair>
FunctionCapture::capture(const GumboNode * node) const
{
  assert(this->func_);
  if( !this->func_ )
    return {};

  auto str = this->func_(node);
  if( this->rx_ )
  {
    boost::match_results<std::string::iterator> mr;
    if( boost::regex_search(str.begin(), str.end(), mr, this->rx_.get()) )
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


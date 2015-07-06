#include "hext/pattern/BuiltinCapture.h"


namespace hext {


BuiltinCapture::BuiltinCapture(
  BuiltinFuncPtr func,
  std::string result_name,
  boost::optional<boost::regex> regex
)
: func_(func)
, name_(std::move(result_name))
, rx_(std::move(regex))
{
}

boost::optional<ResultPair>
BuiltinCapture::capture(const GumboNode * node) const
{
  assert(this->func_);
  if( !this->func_ )
    return boost::optional<ResultPair>();

  std::string val = this->func_(node);
  if( this->rx_ )
  {
    boost::match_results<std::string::iterator> mr;
    if( boost::regex_search(val.begin(), val.end(), mr, this->rx_.get()) )
    {
      // If there are no parentheses contained within the regex, return whole
      // regex capture (mr[0]), if there are, then return the first one.
      return ResultPair(
        this->name_,
        mr.size() > 1 ? mr[1] : mr[0]
      );
    }
    else
    {
      return boost::optional<ResultPair>();
    }
  }
  else
  {
    return ResultPair(this->name_, val);
  }
}


} // namespace hext


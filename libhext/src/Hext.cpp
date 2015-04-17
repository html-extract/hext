#include "hext/Hext.h"


namespace hext {


Hext::Hext(const std::string& hext, Option flags)
: rules_()
, flags_(flags)
{
  Parser p(hext.c_str(), hext.c_str() + hext.size());
  this->rules_ = p.parse(this->flags_);
}

Result Hext::extract(const std::string& html) const
{
  return this->extract(Html(html.c_str(), html.c_str() + html.size()));
}

Result Hext::extract(const Html& html) const
{
  std::vector<Result> results;
  for(const auto& rule : this->rules_)
  {
    ResultTree rt = html.extract(rule);

    if( this->flags_ & Option::RemoveIncomplete )
      rt.remove_incomplete_branches();

    auto result = rt.to_result();
    results.push_back(result);
  }

  hext::Result flat_result;
  if( this->flags_ & Option::InterleaveResults )
  {
    typedef Result::const_iterator result_iter;
    std::vector<std::pair<result_iter, result_iter>> iterators;
    std::vector<Result>::size_type max_size = 0;
    for(const auto& sub_result : results)
    {
      iterators.push_back(std::make_pair(sub_result.begin(), sub_result.end()));
      max_size = std::max(max_size, sub_result.size());
    }

    flat_result.reserve(max_size);
    for(std::vector<Result>::size_type i = 0; i < max_size; ++i)
    {
      flat_result.push_back(ResultMap());
      for(auto& ip : iterators)
      {
        if( ip.first != ip.second )
        {
          flat_result[i].insert(ip.first->begin(), ip.first->end());
          ip.first++;
        }
      }
    }
  }
  else
  {
    for(const auto& sub_result : results)
    {
      flat_result.insert(flat_result.end(), sub_result.begin(), sub_result.end());
    }
  }

  return flat_result;
}


} // namespace hext


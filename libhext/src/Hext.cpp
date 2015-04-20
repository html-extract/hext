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
    ResultTree rt(nullptr);
    rule.extract(html.root(), &rt);

    if( this->flags_ & Option::RemoveIncomplete )
      rt.remove_incomplete_branches();

    results.push_back(rt.to_result());
  }

  hext::Result flat_result;
  if( this->flags_ & Option::InterleaveResults )
  {
    typedef Result::const_iterator result_iter;

    // Collect begin and end of each ResultMap.
    std::vector<std::pair<result_iter, result_iter>> iterators;
    iterators.reserve(this->rules_.size());

    // The size of the biggest ResultMap.
    std::vector<Result>::size_type max_size = 0;

    for(const auto& sub_result : results)
    {
      iterators.push_back(std::make_pair(sub_result.begin(), sub_result.end()));
      max_size = std::max(max_size, sub_result.size());
    }

    // Merge multiple results into a single hext::Result. See "Result
    // flattening" in Hext.h.
    //
    // Example results:
    //   Result#1: [1,2,3,4]
    //   Result#2: [A,B,C,D,E]
    //   Result#3: [X,Y,Z]
    // Expected flat_result:
    //   Result: [1AX, 2BY, 3CZ, 4D, E]
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
    // Copy all vectors into a single one.
    for(const auto& sub_result : results)
    {
      flat_result.insert(flat_result.end(), sub_result.begin(), sub_result.end());
    }
  }

  return flat_result;
}


} // namespace hext


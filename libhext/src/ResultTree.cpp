#include "hext/ResultTree.h"
#include "hext/Rule.h"


namespace hext {


ResultTree::ResultTree(const Rule * rule)
: children_(),
  values_(),
  matching_rule_(rule)
{
}

ResultTree::ResultTree(const Rule * rule, std::vector<ResultPair> values)
: children_(),
  values_(values),
  matching_rule_(rule)
{
}

ResultTree * ResultTree::create_branch(
  const Rule * rule,
  std::vector<ResultPair> values
)
{
  this->children_.push_back(MakeUnique<ResultTree>(rule, values));
  return this->children_.back().get();
}

void ResultTree::delete_branch(const ResultTree * child)
{
  // std::unique_ptr has no operator==(T*)

  for(auto it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    if( it->get() == child )
    {
      this->children_.erase(it);
      // careful: it is now invalid
      return;
    }
  }

  assert(false);
}

Result ResultTree::to_result() const
{
  typedef std::vector<std::unique_ptr<ResultTree>>::size_type c_size_type;

  Result results(this->children_.size());

  for(c_size_type i = 0; i < this->children_.size(); ++i)
    this->children_[i]->save(results[i]);

  return results;
}

void ResultTree::save(std::multimap<std::string, std::string>& map) const
{
  for(const auto& p : this->values_)
    map.insert(p);

  for(const auto& c : this->children_)
    c->save(map);
}


} // namespace hext


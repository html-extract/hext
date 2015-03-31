#include "hext/ResultTree.h"
#include "hext/Rule.h"


namespace hext {


ResultTree::ResultTree(const Rule * rule)
: children_(),
  values_(),
  matching_rule_(rule)
{
}

ResultTree::ResultTree(const Rule * rule, std::vector<NameValuePair> values)
: children_(),
  values_(values),
  matching_rule_(rule)
{
}

ResultTree * ResultTree::create_branch(
  const Rule * rule,
  std::vector<NameValuePair> values
)
{
  this->children_.push_back(MakeUnique<ResultTree>(rule, values));
  return this->children_.back().get();
}

void ResultTree::remove_incomplete_branches()
{
  // Hide return type of `ResultTree::filter()`.
  this->filter();
}

Result ResultTree::to_result() const
{
  typedef std::vector<std::unique_ptr<ResultTree>>::size_type c_size_type;

  Result results(this->children_.size());

  for(c_size_type i = 0; i < this->children_.size(); ++i)
    this->children_[i]->save(results[i]);

  return results;
}

bool ResultTree::filter()
{
  // Depth first.
  for(auto& c : this->children_)
    if( c->filter() )
      c.reset(nullptr);

  // Erase all empty unique_ptr.
  this->children_.erase(
    std::remove(this->children_.begin(), this->children_.end(), nullptr),
    this->children_.end()
  );

  // Check if all rules are present in this ResultTree.
  if( this->matching_rule_ )
  {
    auto c_begin = this->children_.begin();
    auto c_end = this->children_.end();

    const auto& rule_children = this->matching_rule_->children();
    auto r_begin = rule_children.begin();
    auto r_end = rule_children.end();

    // All rule-children of the matching rule must be contained in this RuleTree
    // branch's children. Duplicates are safe to ignore.
    // We can take advantage of the fact that ResultTrees are appended in the
    // same order as Rule-children are stored.
    while( r_begin != r_end )
    {
      // Skip matching rules.
      if( c_begin != c_end && (*c_begin)->matching_rule_ == &(*r_begin) )
      {
        // Skip all duplicates.
        while( c_begin != c_end && (*c_begin)->matching_rule_ == &(*r_begin) )
          c_begin++;
      }
      // Skip optional rules.
      else if( !r_begin->optional() )
      {
        // remove
        return true;
      }

      // Rule is satisfied, proceed.
      r_begin++;
    }
  }

  // keep
  return false;
}

void ResultTree::save(std::multimap<std::string, std::string>& map) const
{
  for(const auto& p : this->values_)
    map.insert(p);

  for(const auto& c : this->children_)
    c->save(map);
}


} // namespace hext


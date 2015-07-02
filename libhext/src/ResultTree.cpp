#include "hext/ResultTree.h"
#include "hext/MakeUnique.h"

#include <cassert>


namespace hext {


struct ResultTree::Impl
{
  Impl()
  : children_(),
    values_()
  {
  }

  /// Recursively insert all `values_` into `map`, including this instance's
  /// `values_`.
  void save(ResultMap& map) const
  {
    for(const auto& p : this->values_)
      map.insert(p);

    for(const auto& c : this->children_)
      c->impl_->save(map);
  }

  std::vector<std::unique_ptr<ResultTree>> children_;
  std::vector<ResultPair> values_;
};


ResultTree::ResultTree()
: impl_(MakeUnique<Impl>())
{
}

ResultTree::ResultTree(ResultTree&&) = default;
ResultTree& ResultTree::operator=(ResultTree&&) = default;
ResultTree::~ResultTree() = default;

ResultTree * ResultTree::create_child()
{
  this->impl_->children_.push_back(MakeUnique<ResultTree>());
  return this->impl_->children_.back().get();
}

void ResultTree::delete_child(const ResultTree * child)
{
  // std::unique_ptr has no operator==(T*)

  for(auto it = this->impl_->children_.begin();
      it != this->impl_->children_.end();
      ++it)
  {
    if( it->get() == child )
    {
      this->impl_->children_.erase(it);
      // careful: it is now invalid
      return;
    }
  }

  assert(false);
}

void ResultTree::set_values(std::vector<ResultPair> v)
{
  this->impl_->values_ = std::move(v);
}

const std::vector<ResultPair>& ResultTree::values() const
{
  return this->impl_->values_;
}

const std::vector<std::unique_ptr<ResultTree>>& ResultTree::children() const
{
  return this->impl_->children_;
}

Result ResultTree::flatten() const
{
  typedef std::vector<std::unique_ptr<ResultTree>>::size_type c_size_type;

  Result results(this->impl_->children_.size());

  for(c_size_type i = 0; i < this->impl_->children_.size(); ++i)
    this->impl_->children_[i]->impl_->save(results[i]);

  return results;
}


} // namespace hext


#include "hext/ResultTree.h"

#include <cassert>
#include <iostream> // remove me


namespace hext {


struct ResultTree::Impl
{
  Impl() noexcept
  : children_(),  // noexcept since C++17
    values_()     // noexcept since C++17
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
: impl_(std::make_unique<Impl>())
{
}

ResultTree::~ResultTree() noexcept = default;
ResultTree::ResultTree(ResultTree&&) noexcept = default;
ResultTree& ResultTree::operator=(ResultTree&&) noexcept = default;

ResultTree * ResultTree::create_child()
{
  this->impl_->children_.push_back(std::make_unique<ResultTree>());
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
      // iterator is now invalid
      return;
    }
  }

  assert(false);
}

void ResultTree::set_values(std::vector<ResultPair> v) noexcept
{
  this->impl_->values_ = std::move(v);
}

const std::vector<ResultPair>& ResultTree::values() const noexcept
{
  return this->impl_->values_;
}

const std::vector<std::unique_ptr<ResultTree>>&
ResultTree::children() const noexcept
{
  return this->impl_->children_;
}

Result ResultTree::flatten() const
{
  Result results;
  for(const auto& child : this->impl_->children_)
  {
    ResultMap map;
    child->impl_->save(map);
    if( !map.empty() )
      results.push_back(std::move(map));
  }

  return results;
}


} // namespace hext


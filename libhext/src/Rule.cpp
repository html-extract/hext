// Copyright 2019-2021 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "hext/Rule.h"
#include "RuleMatching.h"

#include <utility>


namespace hext {


Rule::Rule(HtmlTag tag,
           bool    optional,
           bool    greedy) noexcept
: first_child_(nullptr)
, next_(nullptr)
, nested_()
, matches_()
, captures_()
, tag_(tag)
, is_optional_(optional)
, is_greedy_(greedy)
, tagname_(std::nullopt)
{
}

Rule::Rule(std::string tag,
           bool        optional,
           bool        greedy) noexcept
: first_child_(nullptr)
, next_(nullptr)
, nested_()
, matches_()
, captures_()
, tag_(static_cast<HtmlTag>(gumbo_tag_enum(tag.c_str())))
, is_optional_(optional)
, is_greedy_(greedy)
, tagname_(this->tag_ == HtmlTag::UNKNOWN
           ? std::optional<std::string>(tag)
           : std::nullopt)
{
}

Rule::Rule(const Rule& other)
: first_child_(nullptr)
, next_(nullptr)
, nested_(other.nested_)
, matches_()
, captures_()
, tag_(other.tag_)
, is_optional_(other.is_optional_)
, is_greedy_(other.is_greedy_)
, tagname_(other.tagname_)
{
  if( other.first_child_ )
    this->first_child_ = std::make_unique<Rule>(*(other.first_child_));

  if( other.next_ )
    this->next_ = std::make_unique<Rule>(*(other.next_));

  this->matches_.reserve(other.matches_.size());
  for(const auto& m : other.matches_)
    this->matches_.emplace_back(m ? m->clone() : nullptr);

  this->captures_.reserve(other.captures_.size());
  for(const auto& c : other.captures_)
    this->captures_.emplace_back(c ? c->clone() : nullptr);
}

Rule& Rule::operator=(const Rule& other)
{
  Rule tmp(other);
  this->swap(tmp);
  return *this;
}

const Rule * Rule::child() const noexcept
{
  return this->first_child_.get();
}

const Rule * Rule::next() const noexcept
{
  return this->next_.get();
}

const std::vector<Rule>& Rule::nested() const noexcept
{
  return this->nested_;
}

Rule * Rule::child() noexcept
{
  return this->first_child_.get();
}

Rule * Rule::next() noexcept
{
  return this->next_.get();
}

std::vector<Rule>& Rule::nested() noexcept
{
  return this->nested_;
}

Rule& Rule::append_child(Rule new_child)
{
  if( this->first_child_ )
    this->first_child_->append_next(std::move(new_child));
  else
    this->first_child_ = std::make_unique<Rule>(std::move(new_child));

  return *this;
}

Rule& Rule::append_next(Rule sibling)
{
  Rule * target = this;
  while( target->next_ )
    target = target->next_.get();

  target->next_ = std::make_unique<Rule>(std::move(sibling));
  return *this;
}

Rule& Rule::append_nested(Rule nested)
{
  this->nested_.push_back(std::move(nested));
  return *this;
}

Rule& Rule::append_match(std::unique_ptr<Match> match)
{
  this->matches_.push_back(std::move(match));
  return *this;
}

Rule& Rule::append_capture(std::unique_ptr<Capture> cap)
{
  this->captures_.push_back(std::move(cap));
  return *this;
}

HtmlTag Rule::get_tag() const noexcept
{
  return this->tag_;
}

Rule& Rule::set_tag(HtmlTag tag) noexcept
{
  this->tag_ = tag;
  return *this;
}

bool Rule::is_optional() const noexcept
{
  return this->is_optional_;
}

Rule& Rule::set_optional(bool optional) noexcept
{
  this->is_optional_ = optional;
  return *this;
}

bool Rule::is_greedy() const noexcept
{
  return this->is_greedy_;
}

Rule& Rule::set_greedy(bool greedy) noexcept
{
  this->is_greedy_ = greedy;
  return *this;
}

std::optional<std::string> Rule::get_tagname() const
{
  return this->tagname_;
}

Rule& Rule::set_tagname(const std::string& tagname)
{
  this->tagname_ = tagname;
  return *this;
}

bool Rule::matches(const GumboNode * node) const
{
  if( !node )
    return false;

  if( this->tag_ != HtmlTag::ANY )
  {
    if( node->type != GUMBO_NODE_ELEMENT )
      return false;

    if( node->v.element.tag != static_cast<GumboTag>(this->tag_) )
      return false;

    if( this->tag_ == HtmlTag::UNKNOWN )
    {
      if( !this->tagname_
          || node->v.element.original_tag.data == nullptr
          || node->v.element.original_tag.length == 0 )
        return false;

      GumboStringPiece original_tagname = node->v.element.original_tag;
      gumbo_tag_from_original_text(&original_tagname);

      if( this->tagname_->size() != original_tagname.length )
        return false;

      GumboStringPiece this_tagname;
      this_tagname.data = this->tagname_->data();
      this_tagname.length = this->tagname_->size();

      const bool tagname_matches =
        gumbo_string_equals_ignore_case(&this_tagname, &original_tagname);

      if( !tagname_matches )
        return false;
    }
  }

  for( const auto& match : this->matches_ )
    if( match && !match->matches(node) )
      return false;

  return true;
}

std::vector<ResultPair> Rule::capture(const GumboNode * node) const
{
  if( !node )
    return {};

  std::vector<ResultPair> values;
  values.reserve(this->captures_.size());
  for( const auto& cap : this->captures_ )
  {
    if( cap )
    {
      if( auto pair = cap->capture(node) )
      {
        values.push_back(*pair);
      }
    }
  }

  return values;
}

hext::Result Rule::extract(const Html&   html,
                           std::uint64_t max_searches) const
{
  return this->extract(html.root(), max_searches);
}

hext::Result Rule::extract(const GumboNode * node,
                           std::uint64_t     max_searches) const
{
  std::vector<MatchingNodes> mn;
  SaveMatchingNodesRecursive(this, node, mn, max_searches);

  hext::Result result;
  for( const auto& group : mn )
  {
    ResultMap map;
    for( const auto& pair : group )
    {
      if( (pair.first)->captures_.size() )
      {
        auto values = (pair.first)->capture(pair.second);
        if( values.size() )
          map.insert(values.begin(), values.end());
      }
    }

    if( !map.empty() )
    {
      result.push_back(std::move(map));
    }
  }

  return result;
}

void Rule::swap(hext::Rule& other) noexcept
{
  if( this == &other )
    return;

  this->first_child_.swap(other.first_child_);
  this->next_.swap(other.next_);
  this->nested_.swap(other.nested_);
  this->matches_.swap(other.matches_);
  this->captures_.swap(other.captures_);
  std::swap(this->tag_, other.tag_);
  std::swap(this->is_optional_, other.is_optional_);
  std::swap(this->is_greedy_, other.is_greedy_);
  std::swap(this->tagname_, other.tagname_);
}


} // namespace hext


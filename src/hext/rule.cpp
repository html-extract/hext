#include "hext/rule.h"
#include "hext/match-tree.h"


namespace hext {


Rule::Rule(
  GumboTag tag,
  bool is_optional,
  int nth_child,
  bool closed,
  RulePatterns&& r_patterns
)
: children_()
, patterns_(std::move(r_patterns))
, match_count_(0)
, gumbo_tag_(tag)
, is_opt_(is_optional)
, child_pos_(nth_child)
, is_closed_(closed)
{
}

Rule::~Rule()
{
}

Rule::Rule(Rule&& r)
: children_(std::move(r.children_))
, patterns_(std::move(r.patterns_))
, match_count_(r.match_count_.load())
, gumbo_tag_(r.gumbo_tag_)
, is_opt_(r.is_opt_)
, child_pos_(r.child_pos_)
, is_closed_(r.is_closed_)
{
}

void Rule::append_child(Rule&& r, int level)
{
  if( level > 1 && !this->children_.empty() )
  {
    this->children_.back().append_child(std::move(r), level - 1);
    return;
  }

  this->children_.push_back(std::move(r));
}

const std::vector<Rule>& Rule::children() const
{
  return this->children_;
}

GumboTag Rule::gumbo_tag() const
{
  return this->gumbo_tag_;
}

bool Rule::optional() const
{
  return this->is_opt_;
}

void Rule::extract(const GumboNode * node, MatchTree * m) const
{
  if( !node || !m || node->type != GUMBO_NODE_ELEMENT )
    return;

  if( this->matches(node) )
  {
    this->match_count_++;

    // Although we have a match, this may not be the html-node that the user
    // is searching for, so we have to keep matching.
    this->extract_node_children(node, m);

    {
      std::unique_ptr<MatchTree> mt = this->patterns_.capture(node);
      assert(mt != nullptr);
      mt->set_rule(this);
      m = m->append_child_and_own(std::move(mt));
    }

    for(const auto& c : this->children_)
      c.extract_node_children(node, m);
  }
  else
  {
    // if this rule is a direct descendant, and it didn't match,
    // all child-rules cannot be matched either.
    if( this->child_pos_ == -1 )
      this->extract_node_children(node, m);
  }
}

void Rule::print(
  std::ostream& out,
  int indent_level,
  bool print_match_count
) const
{
  if( print_match_count )
    out << "\tx" << this->match_count_ << " |";

  out << ( indent_level ? std::string(indent_level * 2, ' ') : "" )
      << "<"
      << ( this->is_opt_ ? "?" : "" )
      << ( this->child_pos_ == 0 ? "!" : "" );

  if( this->child_pos_ > 0 )
    out << this->child_pos_;

  if( this->gumbo_tag_ != GUMBO_TAG_UNKNOWN )
    out << gumbo_normalized_tagname(this->gumbo_tag_);

  this->patterns_.print(out);

  if( this->is_closed_ )
    out << ">";

  out << "\n";
  for(const auto& c : this->children_)
    c.print(out, indent_level + 1, print_match_count);
}

bool Rule::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  if( this->gumbo_tag_ != GUMBO_TAG_UNKNOWN )
    if( node->v.element.tag != this->gumbo_tag_ )
      return false;

  if( this->child_pos_ > 0 )
  {
    unsigned int pos = GetNodePositionWithinParent(node);
    if( pos != this->child_pos_ )
      return false;
  }

  if( this->is_closed_ )
    return this->patterns_.matches_all_attributes(node);
  else
    return this->patterns_.matches(node);
}

void Rule::extract_node_children(const GumboNode * node, MatchTree * m) const
{
  if( !node || !m || node->type != GUMBO_NODE_ELEMENT )
    return;

  const GumboVector * node_children = &node->v.element.children;
  for(unsigned int i = 0; i < node_children->length; ++i)
  {
    this->extract(
      static_cast<const GumboNode *>(node_children->data[i]),
      m
    );
  }
}


} // namespace hext


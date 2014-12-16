#ifndef HEXT_MATCH_TREE_H
#define HEXT_MATCH_TREE_H

#include <string>
#include <utility>
#include <vector>


namespace hext {


class match_tree
{
public:
  typedef std::vector<match_tree>::const_iterator const_child_iterator;
  typedef 
    std::vector<std::pair<std::string, const char *>>::const_iterator 
    const_match_iterator;

  match_tree()
  : children(),
    matches()
  {
  }

  match_tree& append_child(const match_tree& m)
  {
    this->children.push_back(m);
    return this->children.back();
  }

  // TODO: inconsistent interface: std::string vs. const char *
  void append_match(const std::string& name, const char * value)
  {
    this->matches.push_back(
      std::pair<std::string, const char *>(name, value)
    );
  }

  const_child_iterator children_begin() const
  {
    return this->children.begin();
  }

  const_child_iterator children_end() const
  {
    return this->children.end();
  }

  const_match_iterator matches_begin() const
  {
    return this->matches.begin();
  }

  const_match_iterator matches_end() const
  {
    return this->matches.end();
  }

  // since the pointer members are non-owning, 
  // we can copy them freely
  match_tree(const match_tree&) = default;
  match_tree& operator=(const match_tree&) = default;

private:
  std::vector<match_tree> children;
  std::vector<std::pair<std::string, const char *>> matches;
};


} // namespace hext


#endif // HEXT_MATCH_TREE_H


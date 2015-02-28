#include "hext/match-tree.h"
#include "hext/make-unique.h"

#include <memory>

#include <rapidjson/document.h>


namespace {


TEST(MatchTree_AppendChildAndOwn, Append)
{
  hext::MatchTree mt;
  std::unique_ptr<hext::MatchTree> child = hext::MakeUnique<hext::MatchTree>();
  hext::MatchTree * child_ptr = child.get();
  EXPECT_EQ(child_ptr, mt.append_child_and_own(std::move(child)));
}

TEST(MatchTree_AppendMatch, AppendJson)
{
  std::unique_ptr<hext::MatchTree> branch = hext::MakeUnique<hext::MatchTree>();
  branch->append_match(hext::MatchTree::NameValuePair("foo", "bar"));

  hext::MatchTree mt;
  mt.append_child_and_own(std::move(branch));
  std::vector<rapidjson::Document> objects = mt.to_json();
  ASSERT_TRUE(objects.size());
  EXPECT_EQ(objects.front()["foo"], "bar");
}


} // namespace


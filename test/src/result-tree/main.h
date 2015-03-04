#include "hext/result-tree.h"
#include "hext/make-unique.h"

#include <memory>

#include <rapidjson/document.h>


namespace {


TEST(ResultTree_AppendChildAndOwn, Append)
{
  hext::ResultTree rt;
  std::unique_ptr<hext::ResultTree> child = hext::MakeUnique<hext::ResultTree>();
  hext::ResultTree * child_ptr = child.get();
  EXPECT_EQ(child_ptr, rt.append_child_and_own(std::move(child)));
}

TEST(ResultTree_AppendValue, AppendJson)
{
  std::unique_ptr<hext::ResultTree> branch = hext::MakeUnique<hext::ResultTree>();
  branch->append_result(hext::ResultTree::NameValuePair("foo", "bar"));

  hext::ResultTree rt;
  rt.append_child_and_own(std::move(branch));
  std::vector<rapidjson::Document> objects = rt.to_json();
  ASSERT_TRUE(objects.size());
  EXPECT_EQ(objects.front()["foo"], "bar");
}


} // namespace


#include <algorithm>
#include <iterator>
#include <vector>


TEST(ResultTree_ResultTree, HoldsValues)
{
  Result values {
    {
      {"a-key-1","a-val-1"},
      {"a-key-2","a-val-2"},
      {"a-key-3","a-val-3"}
    },
    {
      {"b-key-1","b-val-1"},
      {"b-key-2","b-val-2"},
      {"b-key-3","b-val-3"}
    },
    {
      {"c-key-1","c-val-1"},
      {"c-key-2","c-val-2"},
      {"c-key-3","c-val-3"}
    }
  };

  ResultTree rt;
  for( const auto& v : values )
  {
    auto child = rt.create_child();
    ASSERT_TRUE(child);
    std::vector<ResultPair> vector;
    vector.reserve(v.size());
    std::copy(v.begin(), v.end(), std::back_inserter(vector));
    child->set_values(vector);
    EXPECT_EQ(child->values(), vector);
    EXPECT_EQ(child->children().size(), 0);
  }

  EXPECT_EQ(rt.children().size(), values.size());

  Result from_rt = rt.flatten();

  ASSERT_EQ(values.size(), from_rt.size());
  EXPECT_EQ(values, from_rt);
}

TEST(ResultTree_ResultTree, DeletesChildren)
{
  ResultTree rt;
  EXPECT_EQ(rt.children().size(), 0);
  auto one = rt.create_child();
  ASSERT_EQ(rt.children().size(), 1);
  auto two = rt.create_child();
  ASSERT_EQ(rt.children().size(), 2);
  rt.delete_child(one);
  EXPECT_EQ(rt.children().size(), 1);
  rt.delete_child(two);
  EXPECT_EQ(rt.children().size(), 0);
}


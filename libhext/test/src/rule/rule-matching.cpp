// Copyright 2015 Thomas Trapp
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

#include "helper/common.h"
using namespace hext;

#include "RuleMatching.h"

#include <set>


namespace {

bool result_has_unique_nodes(const std::vector<MatchingNodes>& result)
{
  std::set<const GumboNode *> nodes;

  for( const auto& group : result )
    for( const auto& pair : group )
      if( !nodes.insert(pair.second).second )
        return false;

  return true;
}

bool group_has_unique_rules(const MatchingNodes& group)
{
  std::set<const Rule *> rules;

  for( const auto& pair : group )
    if( !rules.insert(pair.first).second )
      return false;

  return true;
}

}


TEST(Rule_RuleMatching, SaveMatchingNodesRecursive)
{
  THtml h("<div>"
            "<div><ul><li></li><li></li></ul></div>"    // 1
            "<div><ul><li></li><li></li></ul></div>"    // 2
          "</div>"
          "<div>"
            "<div><ul><li></li><li></li></ul></div>"    // 3
            "<div><ul><li></li><li></li></ul></div>"    // 4
          "</div>"
          "<div>"
            "<div><ul><li></li><li></li></ul></div>"    // 5
            "<div>"
              "<ul>"
                "<li></li>"
                "<li></li>"
              "</ul>"
              "<div><ul><li></li><li></li></ul></div>"  // 7
            "</div>"                                    // 6
          "</div>");

  // These rules must all produce the same result
  std::vector<const char *> hext = {
    // only mandatory
    "<div><ul><li/><li/></ul></div>",
    // top-level optional
    "<?div><ul><li/><li/></ul></div>",
    // preceding optional
    "<?div/><div><ul><li/><li/></ul></div>",
    // trailing optional
    "<div><ul><li/><li/></ul></div><?div/>",
    // preceding and trailing optional
    "<?div/><div><ul><li/><li/></ul></div><?div/>",
    // greedy leaves room for mandatory rules
    "<?div/><div><ul><+li/><li/></ul></div><?div/>",
    // everything greedy
    "<?+div/><+div><+ul><+li/><+li/></ul></div><?+div/>"
  };

  for(std::size_t i = 0; i < hext.size(); ++i)
  {
    auto rule = ParseHext(hext.at(i));

    std::vector<MatchingNodes> result;
    SaveMatchingNodesRecursive(&rule, h.root(), result);

    // Expect seven capture groups
    EXPECT_EQ(result.size(), 7)
      << "rule: " << hext.at(i) << "\n";

    // Expect the result to be unique, i.e. there may be no duplicated nodes.
    // No node may be matched more than once.
    EXPECT_TRUE(result_has_unique_nodes(result))
      << "rule: " << hext.at(i) << "\n";

    for( const auto& group : result )
    {
      // Expect each capture group to have four rule-node-pairs
      EXPECT_EQ(group.size(), 4) << "rule: " << hext.at(i) << "\n";

      // Expect each capture group to match each rule only once
      EXPECT_TRUE(group_has_unique_rules(group))
        << "rule: " << hext.at(i) << "\n";

      // Expect them to actually match
      for( const auto& pair : group )
        EXPECT_TRUE((pair.first)->matches(pair.second))
          << "rule: " << hext.at(i) << "\n";
    }
  }
}

TEST(Rule_RuleMatching, MatchRuleGroup)
{
  // Trailing optional rule
  {
    MatchingNodes r;
    THtml h("<a></a><div></div><a></a>");
    auto a_opt_div = ParseHext("<a/><?div/>");
    auto next = MatchRuleGroup(&a_opt_div, h.first(), r);
    ASSERT_EQ(next, h.body_child(3));
    EXPECT_EQ(r.size(), 2);
    r.clear();

    next = MatchRuleGroup(&a_opt_div, next, r);
    EXPECT_EQ(next, nullptr);
    EXPECT_EQ(r.size(), 1);
  }
  // Only optional rules
  {
    MatchingNodes r;
    THtml h("<a></a><div></div><a></a>");
    auto opt_a_opt_div = ParseHext("<?a/><?div/>");
    auto next = MatchRuleGroup(&opt_a_opt_div, h.first(), r);
    ASSERT_EQ(next, h.body_child(3));
    EXPECT_EQ(r.size(), 2);
    r.clear();

    next = MatchRuleGroup(&opt_a_opt_div, next, r);
    EXPECT_EQ(next, nullptr);
    EXPECT_EQ(r.size(), 1);
  }
  // Greedy rule
  {
    MatchingNodes r;
    THtml h("<a></a><div></div><a></a><div></div>");
    auto greedy_a = ParseHext("<+a/>");
    auto next = MatchRuleGroup(&greedy_a, h.first(), r);
    ASSERT_EQ(next, nullptr);
    EXPECT_EQ(r.size(), 2);
  }
}

TEST(Rule_RuleMatching, RuleMatchesNodeRecursive)
{
  MatchingNodes r;
  THtml h("<a><u></u><i></i></a>");
  auto a = ParseHext("<a><u/><i/></a>");

  auto matches = RuleMatchesNodeRecursive(&a, h.first(), r);
  EXPECT_TRUE(matches);
  // r now contains <u> and <i>
  EXPECT_EQ(r.size(), 2);
}

TEST(Rule_RuleMatching, MatchRuleOnce)
{
  {
    MatchingNodes r;
    auto rule_a  = ParseHext("<a/>");
    auto rule_b  = ParseHext("<b/>");
    auto rule_aa = ParseHext("<a/><a/>");
    auto rule_i  = ParseHext("<i/>");
    THtml h("<a></a><b></b>");

    EXPECT_EQ(MatchRuleOnce(&rule_a, h.first(), nullptr, r), h.first());
    EXPECT_EQ(r.size(), 0);

    EXPECT_EQ(MatchRuleOnce(&rule_aa, h.first(), nullptr, r), h.first());
    EXPECT_EQ(r.size(), 0);

    EXPECT_EQ(MatchRuleOnce(&rule_b, h.first(), nullptr, r), h.body_child(2));
    EXPECT_EQ(r.size(), 0);

    EXPECT_EQ(MatchRuleOnce(&rule_i, h.first(), nullptr, r), nullptr);
    EXPECT_EQ(r.size(), 0);
  }
  {
    MatchingNodes r;
    auto rule_a  = ParseHext("<a><u/></a>");
    auto rule_b  = ParseHext("<b><u/></b>");
    auto rule_aa = ParseHext("<a><u/></a><a><u/></a>");
    auto rule_i  = ParseHext("<a><i/></a>");
    THtml h("<a><u></u></a><b><u></u></b>");

    EXPECT_EQ(MatchRuleOnce(&rule_a, h.first(), nullptr, r), h.first());
    EXPECT_EQ(r.size(), 1);
    r.clear();

    EXPECT_EQ(MatchRuleOnce(&rule_aa, h.first(), nullptr, r), h.first());
    EXPECT_EQ(r.size(), 1);
    r.clear();

    EXPECT_EQ(MatchRuleOnce(&rule_b, h.first(), nullptr, r), h.body_child(2));
    EXPECT_EQ(r.size(), 1);
    r.clear();

    EXPECT_EQ(MatchRuleOnce(&rule_i, h.first(), nullptr, r), nullptr);
    EXPECT_EQ(r.size(), 0);
  }
}

TEST(Rule_RuleMatching, MatchRange)
{
  {
    MatchingNodes r;

    auto ab = ParseHext("<a/><b/>");
    THtml h("<a></a><p></p><a></a><p></p><b></b>");

    {
      // Match first rule of ab against "<a></a>"
      auto next = MatchRange(&ab, ab.next(), h.first(), h.body_child(2), r);
      // MatchRange returns the last matched node
      EXPECT_EQ(next, h.first());
      EXPECT_EQ(r.size(), 1);
      r.clear();
    }

    {
      // Match whole rule range against whole node range
      auto next = MatchRange(&ab, nullptr, h.first(), nullptr, r);
      EXPECT_EQ(next, h.body_child(5));
      EXPECT_EQ(r.size(), 2);
      r.clear();
    }
  }
}

TEST(Rule_RuleMatching, FindMandatoryRule)
{
  {
    EXPECT_EQ(FindMandatoryRule(nullptr, nullptr), nullptr);
  }
  {
    auto rule = ParseHext("<a/>");
    EXPECT_EQ(FindMandatoryRule(&rule, nullptr), &rule);
  }
  {
    auto rule = ParseHext("<a/><b/>");
    EXPECT_EQ(FindMandatoryRule(&rule, nullptr), &rule);
    EXPECT_EQ(FindMandatoryRule(rule.next(), nullptr), rule.next());
    EXPECT_EQ(FindMandatoryRule(rule.next()->next(), nullptr), nullptr);
  }
  {
    auto rule = ParseHext("<?a/><b/>");
    EXPECT_EQ(FindMandatoryRule(&rule, nullptr), rule.next());
    EXPECT_EQ(FindMandatoryRule(rule.next(), nullptr), rule.next());
    EXPECT_EQ(FindMandatoryRule(rule.next()->next(), nullptr), nullptr);
  }
  {
    auto rule = ParseHext("<?a/><?b/>");
    EXPECT_EQ(FindMandatoryRule(&rule, nullptr), nullptr);
    EXPECT_EQ(FindMandatoryRule(rule.next(), nullptr), nullptr);
    EXPECT_EQ(FindMandatoryRule(rule.next()->next(), nullptr), nullptr);
  }
  {
    auto rule = ParseHext("<a/><?b/><i/>");
    EXPECT_EQ(FindMandatoryRule(&rule, nullptr), &rule);
    EXPECT_EQ(FindMandatoryRule(rule.next(), nullptr), rule.next()->next());
  }
}


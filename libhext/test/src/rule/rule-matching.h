#include "RuleMatching.h"

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

  auto rule = ParseHext("<div><ul><li/><li/></ul></div>");
  auto opt_rule = ParseHext("<?div><ul><li/><li/></ul></div>");

  ASSERT_EQ(rule.get_tag(), HtmlTag::DIV);
  ASSERT_NE(rule.child(), nullptr);
  ASSERT_EQ(opt_rule.get_tag(), HtmlTag::DIV);
  ASSERT_NE(opt_rule.child(), nullptr);

  std::vector<MatchingNodes> result;
  SaveMatchingNodesRecursive(&rule, h.root(), result);
  std::vector<MatchingNodes> opt_result;
  SaveMatchingNodesRecursive(&opt_rule, h.root(), opt_result);

  // Expect seven capture groups
  EXPECT_EQ(result.size(), 7);
  EXPECT_EQ(opt_result.size(), 7);

  for( const auto& group : result )
  {
    // Expect each capture group to have four matching rule-node-pairs
    EXPECT_EQ(group.size(), 4);
    for( const auto& pair : group )
      EXPECT_TRUE((pair.first)->matches(pair.second));
  }
  for( const auto& group : opt_result )
  {
    // Expect each capture group to have four matching rule-node-pairs
    EXPECT_EQ(group.size(), 4);
    for( const auto& pair : group )
      EXPECT_TRUE((pair.first)->matches(pair.second));
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


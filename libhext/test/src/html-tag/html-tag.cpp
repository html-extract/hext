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


TEST(HtmlTag_HtmlTag, EqualsGumboTag)
{
  EXPECT_EQ(static_cast<int>(HtmlTag::HTML), static_cast<int>(GUMBO_TAG_HTML));
  EXPECT_EQ(static_cast<int>(HtmlTag::HEAD), static_cast<int>(GUMBO_TAG_HEAD));
  EXPECT_EQ(static_cast<int>(HtmlTag::TITLE), static_cast<int>(GUMBO_TAG_TITLE));
  EXPECT_EQ(static_cast<int>(HtmlTag::BASE), static_cast<int>(GUMBO_TAG_BASE));
  EXPECT_EQ(static_cast<int>(HtmlTag::LINK), static_cast<int>(GUMBO_TAG_LINK));
  EXPECT_EQ(static_cast<int>(HtmlTag::META), static_cast<int>(GUMBO_TAG_META));
  EXPECT_EQ(static_cast<int>(HtmlTag::STYLE), static_cast<int>(GUMBO_TAG_STYLE));
  EXPECT_EQ(static_cast<int>(HtmlTag::SCRIPT), static_cast<int>(GUMBO_TAG_SCRIPT));
  EXPECT_EQ(static_cast<int>(HtmlTag::NOSCRIPT), static_cast<int>(GUMBO_TAG_NOSCRIPT));
  EXPECT_EQ(static_cast<int>(HtmlTag::TEMPLATE), static_cast<int>(GUMBO_TAG_TEMPLATE));
  EXPECT_EQ(static_cast<int>(HtmlTag::BODY), static_cast<int>(GUMBO_TAG_BODY));
  EXPECT_EQ(static_cast<int>(HtmlTag::ARTICLE), static_cast<int>(GUMBO_TAG_ARTICLE));
  EXPECT_EQ(static_cast<int>(HtmlTag::SECTION), static_cast<int>(GUMBO_TAG_SECTION));
  EXPECT_EQ(static_cast<int>(HtmlTag::NAV), static_cast<int>(GUMBO_TAG_NAV));
  EXPECT_EQ(static_cast<int>(HtmlTag::ASIDE), static_cast<int>(GUMBO_TAG_ASIDE));
  EXPECT_EQ(static_cast<int>(HtmlTag::H1), static_cast<int>(GUMBO_TAG_H1));
  EXPECT_EQ(static_cast<int>(HtmlTag::H2), static_cast<int>(GUMBO_TAG_H2));
  EXPECT_EQ(static_cast<int>(HtmlTag::H3), static_cast<int>(GUMBO_TAG_H3));
  EXPECT_EQ(static_cast<int>(HtmlTag::H4), static_cast<int>(GUMBO_TAG_H4));
  EXPECT_EQ(static_cast<int>(HtmlTag::H5), static_cast<int>(GUMBO_TAG_H5));
  EXPECT_EQ(static_cast<int>(HtmlTag::H6), static_cast<int>(GUMBO_TAG_H6));
  EXPECT_EQ(static_cast<int>(HtmlTag::HGROUP), static_cast<int>(GUMBO_TAG_HGROUP));
  EXPECT_EQ(static_cast<int>(HtmlTag::HEADER), static_cast<int>(GUMBO_TAG_HEADER));
  EXPECT_EQ(static_cast<int>(HtmlTag::FOOTER), static_cast<int>(GUMBO_TAG_FOOTER));
  EXPECT_EQ(static_cast<int>(HtmlTag::ADDRESS), static_cast<int>(GUMBO_TAG_ADDRESS));
  EXPECT_EQ(static_cast<int>(HtmlTag::P), static_cast<int>(GUMBO_TAG_P));
  EXPECT_EQ(static_cast<int>(HtmlTag::HR), static_cast<int>(GUMBO_TAG_HR));
  EXPECT_EQ(static_cast<int>(HtmlTag::PRE), static_cast<int>(GUMBO_TAG_PRE));
  EXPECT_EQ(static_cast<int>(HtmlTag::BLOCKQUOTE), static_cast<int>(GUMBO_TAG_BLOCKQUOTE));
  EXPECT_EQ(static_cast<int>(HtmlTag::OL), static_cast<int>(GUMBO_TAG_OL));
  EXPECT_EQ(static_cast<int>(HtmlTag::UL), static_cast<int>(GUMBO_TAG_UL));
  EXPECT_EQ(static_cast<int>(HtmlTag::LI), static_cast<int>(GUMBO_TAG_LI));
  EXPECT_EQ(static_cast<int>(HtmlTag::DL), static_cast<int>(GUMBO_TAG_DL));
  EXPECT_EQ(static_cast<int>(HtmlTag::DT), static_cast<int>(GUMBO_TAG_DT));
  EXPECT_EQ(static_cast<int>(HtmlTag::DD), static_cast<int>(GUMBO_TAG_DD));
  EXPECT_EQ(static_cast<int>(HtmlTag::FIGURE), static_cast<int>(GUMBO_TAG_FIGURE));
  EXPECT_EQ(static_cast<int>(HtmlTag::FIGCAPTION), static_cast<int>(GUMBO_TAG_FIGCAPTION));
  EXPECT_EQ(static_cast<int>(HtmlTag::MAIN), static_cast<int>(GUMBO_TAG_MAIN));
  EXPECT_EQ(static_cast<int>(HtmlTag::DIV), static_cast<int>(GUMBO_TAG_DIV));
  EXPECT_EQ(static_cast<int>(HtmlTag::A), static_cast<int>(GUMBO_TAG_A));
  EXPECT_EQ(static_cast<int>(HtmlTag::EM), static_cast<int>(GUMBO_TAG_EM));
  EXPECT_EQ(static_cast<int>(HtmlTag::STRONG), static_cast<int>(GUMBO_TAG_STRONG));
  EXPECT_EQ(static_cast<int>(HtmlTag::SMALL), static_cast<int>(GUMBO_TAG_SMALL));
  EXPECT_EQ(static_cast<int>(HtmlTag::S), static_cast<int>(GUMBO_TAG_S));
  EXPECT_EQ(static_cast<int>(HtmlTag::CITE), static_cast<int>(GUMBO_TAG_CITE));
  EXPECT_EQ(static_cast<int>(HtmlTag::Q), static_cast<int>(GUMBO_TAG_Q));
  EXPECT_EQ(static_cast<int>(HtmlTag::DFN), static_cast<int>(GUMBO_TAG_DFN));
  EXPECT_EQ(static_cast<int>(HtmlTag::ABBR), static_cast<int>(GUMBO_TAG_ABBR));
  EXPECT_EQ(static_cast<int>(HtmlTag::DATA), static_cast<int>(GUMBO_TAG_DATA));
  EXPECT_EQ(static_cast<int>(HtmlTag::TIME), static_cast<int>(GUMBO_TAG_TIME));
  EXPECT_EQ(static_cast<int>(HtmlTag::CODE), static_cast<int>(GUMBO_TAG_CODE));
  EXPECT_EQ(static_cast<int>(HtmlTag::VAR), static_cast<int>(GUMBO_TAG_VAR));
  EXPECT_EQ(static_cast<int>(HtmlTag::SAMP), static_cast<int>(GUMBO_TAG_SAMP));
  EXPECT_EQ(static_cast<int>(HtmlTag::KBD), static_cast<int>(GUMBO_TAG_KBD));
  EXPECT_EQ(static_cast<int>(HtmlTag::SUB), static_cast<int>(GUMBO_TAG_SUB));
  EXPECT_EQ(static_cast<int>(HtmlTag::SUP), static_cast<int>(GUMBO_TAG_SUP));
  EXPECT_EQ(static_cast<int>(HtmlTag::I), static_cast<int>(GUMBO_TAG_I));
  EXPECT_EQ(static_cast<int>(HtmlTag::B), static_cast<int>(GUMBO_TAG_B));
  EXPECT_EQ(static_cast<int>(HtmlTag::U), static_cast<int>(GUMBO_TAG_U));
  EXPECT_EQ(static_cast<int>(HtmlTag::MARK), static_cast<int>(GUMBO_TAG_MARK));
  EXPECT_EQ(static_cast<int>(HtmlTag::RUBY), static_cast<int>(GUMBO_TAG_RUBY));
  EXPECT_EQ(static_cast<int>(HtmlTag::RT), static_cast<int>(GUMBO_TAG_RT));
  EXPECT_EQ(static_cast<int>(HtmlTag::RP), static_cast<int>(GUMBO_TAG_RP));
  EXPECT_EQ(static_cast<int>(HtmlTag::BDI), static_cast<int>(GUMBO_TAG_BDI));
  EXPECT_EQ(static_cast<int>(HtmlTag::BDO), static_cast<int>(GUMBO_TAG_BDO));
  EXPECT_EQ(static_cast<int>(HtmlTag::SPAN), static_cast<int>(GUMBO_TAG_SPAN));
  EXPECT_EQ(static_cast<int>(HtmlTag::BR), static_cast<int>(GUMBO_TAG_BR));
  EXPECT_EQ(static_cast<int>(HtmlTag::WBR), static_cast<int>(GUMBO_TAG_WBR));
  EXPECT_EQ(static_cast<int>(HtmlTag::INS), static_cast<int>(GUMBO_TAG_INS));
  EXPECT_EQ(static_cast<int>(HtmlTag::DEL), static_cast<int>(GUMBO_TAG_DEL));
  EXPECT_EQ(static_cast<int>(HtmlTag::IMAGE), static_cast<int>(GUMBO_TAG_IMAGE));
  EXPECT_EQ(static_cast<int>(HtmlTag::IMG), static_cast<int>(GUMBO_TAG_IMG));
  EXPECT_EQ(static_cast<int>(HtmlTag::IFRAME), static_cast<int>(GUMBO_TAG_IFRAME));
  EXPECT_EQ(static_cast<int>(HtmlTag::EMBED), static_cast<int>(GUMBO_TAG_EMBED));
  EXPECT_EQ(static_cast<int>(HtmlTag::OBJECT), static_cast<int>(GUMBO_TAG_OBJECT));
  EXPECT_EQ(static_cast<int>(HtmlTag::PARAM), static_cast<int>(GUMBO_TAG_PARAM));
  EXPECT_EQ(static_cast<int>(HtmlTag::VIDEO), static_cast<int>(GUMBO_TAG_VIDEO));
  EXPECT_EQ(static_cast<int>(HtmlTag::AUDIO), static_cast<int>(GUMBO_TAG_AUDIO));
  EXPECT_EQ(static_cast<int>(HtmlTag::SOURCE), static_cast<int>(GUMBO_TAG_SOURCE));
  EXPECT_EQ(static_cast<int>(HtmlTag::TRACK), static_cast<int>(GUMBO_TAG_TRACK));
  EXPECT_EQ(static_cast<int>(HtmlTag::CANVAS), static_cast<int>(GUMBO_TAG_CANVAS));
  EXPECT_EQ(static_cast<int>(HtmlTag::MAP), static_cast<int>(GUMBO_TAG_MAP));
  EXPECT_EQ(static_cast<int>(HtmlTag::AREA), static_cast<int>(GUMBO_TAG_AREA));
  EXPECT_EQ(static_cast<int>(HtmlTag::MATH), static_cast<int>(GUMBO_TAG_MATH));
  EXPECT_EQ(static_cast<int>(HtmlTag::MI), static_cast<int>(GUMBO_TAG_MI));
  EXPECT_EQ(static_cast<int>(HtmlTag::MO), static_cast<int>(GUMBO_TAG_MO));
  EXPECT_EQ(static_cast<int>(HtmlTag::MN), static_cast<int>(GUMBO_TAG_MN));
  EXPECT_EQ(static_cast<int>(HtmlTag::MS), static_cast<int>(GUMBO_TAG_MS));
  EXPECT_EQ(static_cast<int>(HtmlTag::MTEXT), static_cast<int>(GUMBO_TAG_MTEXT));
  EXPECT_EQ(static_cast<int>(HtmlTag::MGLYPH), static_cast<int>(GUMBO_TAG_MGLYPH));
  EXPECT_EQ(static_cast<int>(HtmlTag::MALIGNMARK), static_cast<int>(GUMBO_TAG_MALIGNMARK));
  EXPECT_EQ(static_cast<int>(HtmlTag::ANNOTATION_XML), static_cast<int>(GUMBO_TAG_ANNOTATION_XML));
  EXPECT_EQ(static_cast<int>(HtmlTag::SVG), static_cast<int>(GUMBO_TAG_SVG));
  EXPECT_EQ(static_cast<int>(HtmlTag::FOREIGNOBJECT), static_cast<int>(GUMBO_TAG_FOREIGNOBJECT));
  EXPECT_EQ(static_cast<int>(HtmlTag::DESC), static_cast<int>(GUMBO_TAG_DESC));
  EXPECT_EQ(static_cast<int>(HtmlTag::TABLE), static_cast<int>(GUMBO_TAG_TABLE));
  EXPECT_EQ(static_cast<int>(HtmlTag::CAPTION), static_cast<int>(GUMBO_TAG_CAPTION));
  EXPECT_EQ(static_cast<int>(HtmlTag::COLGROUP), static_cast<int>(GUMBO_TAG_COLGROUP));
  EXPECT_EQ(static_cast<int>(HtmlTag::COL), static_cast<int>(GUMBO_TAG_COL));
  EXPECT_EQ(static_cast<int>(HtmlTag::TBODY), static_cast<int>(GUMBO_TAG_TBODY));
  EXPECT_EQ(static_cast<int>(HtmlTag::THEAD), static_cast<int>(GUMBO_TAG_THEAD));
  EXPECT_EQ(static_cast<int>(HtmlTag::TFOOT), static_cast<int>(GUMBO_TAG_TFOOT));
  EXPECT_EQ(static_cast<int>(HtmlTag::TR), static_cast<int>(GUMBO_TAG_TR));
  EXPECT_EQ(static_cast<int>(HtmlTag::TD), static_cast<int>(GUMBO_TAG_TD));
  EXPECT_EQ(static_cast<int>(HtmlTag::TH), static_cast<int>(GUMBO_TAG_TH));
  EXPECT_EQ(static_cast<int>(HtmlTag::FORM), static_cast<int>(GUMBO_TAG_FORM));
  EXPECT_EQ(static_cast<int>(HtmlTag::FIELDSET), static_cast<int>(GUMBO_TAG_FIELDSET));
  EXPECT_EQ(static_cast<int>(HtmlTag::LEGEND), static_cast<int>(GUMBO_TAG_LEGEND));
  EXPECT_EQ(static_cast<int>(HtmlTag::LABEL), static_cast<int>(GUMBO_TAG_LABEL));
  EXPECT_EQ(static_cast<int>(HtmlTag::INPUT), static_cast<int>(GUMBO_TAG_INPUT));
  EXPECT_EQ(static_cast<int>(HtmlTag::BUTTON), static_cast<int>(GUMBO_TAG_BUTTON));
  EXPECT_EQ(static_cast<int>(HtmlTag::SELECT), static_cast<int>(GUMBO_TAG_SELECT));
  EXPECT_EQ(static_cast<int>(HtmlTag::DATALIST), static_cast<int>(GUMBO_TAG_DATALIST));
  EXPECT_EQ(static_cast<int>(HtmlTag::OPTGROUP), static_cast<int>(GUMBO_TAG_OPTGROUP));
  EXPECT_EQ(static_cast<int>(HtmlTag::OPTION), static_cast<int>(GUMBO_TAG_OPTION));
  EXPECT_EQ(static_cast<int>(HtmlTag::TEXTAREA), static_cast<int>(GUMBO_TAG_TEXTAREA));
  EXPECT_EQ(static_cast<int>(HtmlTag::KEYGEN), static_cast<int>(GUMBO_TAG_KEYGEN));
  EXPECT_EQ(static_cast<int>(HtmlTag::OUTPUT), static_cast<int>(GUMBO_TAG_OUTPUT));
  EXPECT_EQ(static_cast<int>(HtmlTag::PROGRESS), static_cast<int>(GUMBO_TAG_PROGRESS));
  EXPECT_EQ(static_cast<int>(HtmlTag::METER), static_cast<int>(GUMBO_TAG_METER));
  EXPECT_EQ(static_cast<int>(HtmlTag::DETAILS), static_cast<int>(GUMBO_TAG_DETAILS));
  EXPECT_EQ(static_cast<int>(HtmlTag::SUMMARY), static_cast<int>(GUMBO_TAG_SUMMARY));
  EXPECT_EQ(static_cast<int>(HtmlTag::MENU), static_cast<int>(GUMBO_TAG_MENU));
  EXPECT_EQ(static_cast<int>(HtmlTag::MENUITEM), static_cast<int>(GUMBO_TAG_MENUITEM));
  EXPECT_EQ(static_cast<int>(HtmlTag::APPLET), static_cast<int>(GUMBO_TAG_APPLET));
  EXPECT_EQ(static_cast<int>(HtmlTag::ACRONYM), static_cast<int>(GUMBO_TAG_ACRONYM));
  EXPECT_EQ(static_cast<int>(HtmlTag::BGSOUND), static_cast<int>(GUMBO_TAG_BGSOUND));
  EXPECT_EQ(static_cast<int>(HtmlTag::DIR), static_cast<int>(GUMBO_TAG_DIR));
  EXPECT_EQ(static_cast<int>(HtmlTag::FRAME), static_cast<int>(GUMBO_TAG_FRAME));
  EXPECT_EQ(static_cast<int>(HtmlTag::FRAMESET), static_cast<int>(GUMBO_TAG_FRAMESET));
  EXPECT_EQ(static_cast<int>(HtmlTag::NOFRAMES), static_cast<int>(GUMBO_TAG_NOFRAMES));
  EXPECT_EQ(static_cast<int>(HtmlTag::ISINDEX), static_cast<int>(GUMBO_TAG_ISINDEX));
  EXPECT_EQ(static_cast<int>(HtmlTag::LISTING), static_cast<int>(GUMBO_TAG_LISTING));
  EXPECT_EQ(static_cast<int>(HtmlTag::XMP), static_cast<int>(GUMBO_TAG_XMP));
  EXPECT_EQ(static_cast<int>(HtmlTag::NEXTID), static_cast<int>(GUMBO_TAG_NEXTID));
  EXPECT_EQ(static_cast<int>(HtmlTag::NOEMBED), static_cast<int>(GUMBO_TAG_NOEMBED));
  EXPECT_EQ(static_cast<int>(HtmlTag::PLAINTEXT), static_cast<int>(GUMBO_TAG_PLAINTEXT));
  EXPECT_EQ(static_cast<int>(HtmlTag::RB), static_cast<int>(GUMBO_TAG_RB));
  EXPECT_EQ(static_cast<int>(HtmlTag::STRIKE), static_cast<int>(GUMBO_TAG_STRIKE));
  EXPECT_EQ(static_cast<int>(HtmlTag::BASEFONT), static_cast<int>(GUMBO_TAG_BASEFONT));
  EXPECT_EQ(static_cast<int>(HtmlTag::BIG), static_cast<int>(GUMBO_TAG_BIG));
  EXPECT_EQ(static_cast<int>(HtmlTag::BLINK), static_cast<int>(GUMBO_TAG_BLINK));
  EXPECT_EQ(static_cast<int>(HtmlTag::CENTER), static_cast<int>(GUMBO_TAG_CENTER));
  EXPECT_EQ(static_cast<int>(HtmlTag::FONT), static_cast<int>(GUMBO_TAG_FONT));
  EXPECT_EQ(static_cast<int>(HtmlTag::MARQUEE), static_cast<int>(GUMBO_TAG_MARQUEE));
  EXPECT_EQ(static_cast<int>(HtmlTag::MULTICOL), static_cast<int>(GUMBO_TAG_MULTICOL));
  EXPECT_EQ(static_cast<int>(HtmlTag::NOBR), static_cast<int>(GUMBO_TAG_NOBR));
  EXPECT_EQ(static_cast<int>(HtmlTag::SPACER), static_cast<int>(GUMBO_TAG_SPACER));
  EXPECT_EQ(static_cast<int>(HtmlTag::TT), static_cast<int>(GUMBO_TAG_TT));
  EXPECT_EQ(static_cast<int>(HtmlTag::RTC), static_cast<int>(GUMBO_TAG_RTC));

  EXPECT_EQ(static_cast<int>(HtmlTag::ANY), 512);
}


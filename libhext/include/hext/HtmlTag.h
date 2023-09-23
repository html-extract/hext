// Copyright 2015, 2023 Thomas Trapp
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

#ifndef HEXT_HTML_TAG_H_INCLUDED
#define HEXT_HTML_TAG_H_INCLUDED

/// @file
///   All valid HTML tags.

#include <gumbo.h>


namespace hext {


/// An enum containing all valid HTML tags.
/// With the exception of HtmlTag::ANY, every HtmlTag can be casted to its
/// GumboTag counterpart (same int value).
enum class HtmlTag : int
{
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/html
  HTML = GUMBO_TAG_HTML,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/head
  HEAD = GUMBO_TAG_HEAD,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/title
  TITLE = GUMBO_TAG_TITLE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/base
  BASE = GUMBO_TAG_BASE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/link
  LINK = GUMBO_TAG_LINK,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/meta
  META = GUMBO_TAG_META,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/style
  STYLE = GUMBO_TAG_STYLE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/script
  SCRIPT = GUMBO_TAG_SCRIPT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/noscript
  NOSCRIPT = GUMBO_TAG_NOSCRIPT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/template
  TEMPLATE = GUMBO_TAG_TEMPLATE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/body
  BODY = GUMBO_TAG_BODY,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/article
  ARTICLE = GUMBO_TAG_ARTICLE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/section
  SECTION = GUMBO_TAG_SECTION,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/nav
  NAV = GUMBO_TAG_NAV,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/aside
  ASIDE = GUMBO_TAG_ASIDE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/h1
  H1 = GUMBO_TAG_H1,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/h2
  H2 = GUMBO_TAG_H2,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/h3
  H3 = GUMBO_TAG_H3,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/h4
  H4 = GUMBO_TAG_H4,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/h5
  H5 = GUMBO_TAG_H5,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/h6
  H6 = GUMBO_TAG_H6,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/hgroup
  HGROUP = GUMBO_TAG_HGROUP,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/header
  HEADER = GUMBO_TAG_HEADER,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/footer
  FOOTER = GUMBO_TAG_FOOTER,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/address
  ADDRESS = GUMBO_TAG_ADDRESS,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/p
  P = GUMBO_TAG_P,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/hr
  HR = GUMBO_TAG_HR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/pre
  PRE = GUMBO_TAG_PRE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/blockquote
  BLOCKQUOTE = GUMBO_TAG_BLOCKQUOTE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/ol
  OL = GUMBO_TAG_OL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/ul
  UL = GUMBO_TAG_UL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/li
  LI = GUMBO_TAG_LI,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/dl
  DL = GUMBO_TAG_DL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/dt
  DT = GUMBO_TAG_DT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/dd
  DD = GUMBO_TAG_DD,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/figure
  FIGURE = GUMBO_TAG_FIGURE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/figcaption
  FIGCAPTION = GUMBO_TAG_FIGCAPTION,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/main
  MAIN = GUMBO_TAG_MAIN,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/div
  DIV = GUMBO_TAG_DIV,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/a
  A = GUMBO_TAG_A,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/em
  EM = GUMBO_TAG_EM,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/strong
  STRONG = GUMBO_TAG_STRONG,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/small
  SMALL = GUMBO_TAG_SMALL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/s
  S = GUMBO_TAG_S,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/cite
  CITE = GUMBO_TAG_CITE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/q
  Q = GUMBO_TAG_Q,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/dfn
  DFN = GUMBO_TAG_DFN,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/abbr
  ABBR = GUMBO_TAG_ABBR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/data
  DATA = GUMBO_TAG_DATA,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/time
  TIME = GUMBO_TAG_TIME,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/code
  CODE = GUMBO_TAG_CODE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/var
  VAR = GUMBO_TAG_VAR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/samp
  SAMP = GUMBO_TAG_SAMP,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/kbd
  KBD = GUMBO_TAG_KBD,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/sub
  SUB = GUMBO_TAG_SUB,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/sup
  SUP = GUMBO_TAG_SUP,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/i
  I = GUMBO_TAG_I,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/b
  B = GUMBO_TAG_B,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/u
  U = GUMBO_TAG_U,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/mark
  MARK = GUMBO_TAG_MARK,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/ruby
  RUBY = GUMBO_TAG_RUBY,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/rt
  RT = GUMBO_TAG_RT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/rp
  RP = GUMBO_TAG_RP,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/bdi
  BDI = GUMBO_TAG_BDI,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/bdo
  BDO = GUMBO_TAG_BDO,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/span
  SPAN = GUMBO_TAG_SPAN,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/br
  BR = GUMBO_TAG_BR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/wbr
  WBR = GUMBO_TAG_WBR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/ins
  INS = GUMBO_TAG_INS,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/del
  DEL = GUMBO_TAG_DEL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/image
  IMAGE = GUMBO_TAG_IMAGE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/img
  IMG = GUMBO_TAG_IMG,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/iframe
  IFRAME = GUMBO_TAG_IFRAME,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/embed
  EMBED = GUMBO_TAG_EMBED,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/object
  OBJECT = GUMBO_TAG_OBJECT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/param
  PARAM = GUMBO_TAG_PARAM,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/video
  VIDEO = GUMBO_TAG_VIDEO,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/audio
  AUDIO = GUMBO_TAG_AUDIO,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/source
  SOURCE = GUMBO_TAG_SOURCE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/track
  TRACK = GUMBO_TAG_TRACK,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/canvas
  CANVAS = GUMBO_TAG_CANVAS,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/map
  MAP = GUMBO_TAG_MAP,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/area
  AREA = GUMBO_TAG_AREA,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/math
  MATH = GUMBO_TAG_MATH,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/mi
  MI = GUMBO_TAG_MI,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/mo
  MO = GUMBO_TAG_MO,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/mn
  MN = GUMBO_TAG_MN,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/ms
  MS = GUMBO_TAG_MS,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/mtext
  MTEXT = GUMBO_TAG_MTEXT,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/mglyph
  MGLYPH = GUMBO_TAG_MGLYPH,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element
  MALIGNMARK = GUMBO_TAG_MALIGNMARK,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/semantics
  ANNOTATION_XML = GUMBO_TAG_ANNOTATION_XML,
  /// https://developer.mozilla.org/en-US/docs/Web/SVG/Element/svg
  SVG = GUMBO_TAG_SVG,
  /// https://developer.mozilla.org/en-US/docs/Web/SVG/Element/foreignObject
  FOREIGNOBJECT = GUMBO_TAG_FOREIGNOBJECT,
  /// https://developer.mozilla.org/en-US/docs/Web/SVG/Element/desc
  DESC = GUMBO_TAG_DESC,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/table
  TABLE = GUMBO_TAG_TABLE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/caption
  CAPTION = GUMBO_TAG_CAPTION,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/colgroup
  COLGROUP = GUMBO_TAG_COLGROUP,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/col
  COL = GUMBO_TAG_COL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/tbody
  TBODY = GUMBO_TAG_TBODY,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/thead
  THEAD = GUMBO_TAG_THEAD,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/tfoot
  TFOOT = GUMBO_TAG_TFOOT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/tr
  TR = GUMBO_TAG_TR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/td
  TD = GUMBO_TAG_TD,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/th
  TH = GUMBO_TAG_TH,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/form
  FORM = GUMBO_TAG_FORM,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/fieldset
  FIELDSET = GUMBO_TAG_FIELDSET,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/legend
  LEGEND = GUMBO_TAG_LEGEND,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/label
  LABEL = GUMBO_TAG_LABEL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/input
  INPUT = GUMBO_TAG_INPUT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/button
  BUTTON = GUMBO_TAG_BUTTON,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/select
  SELECT = GUMBO_TAG_SELECT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/datalist
  DATALIST = GUMBO_TAG_DATALIST,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/optgroup
  OPTGROUP = GUMBO_TAG_OPTGROUP,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/option
  OPTION = GUMBO_TAG_OPTION,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/textarea
  TEXTAREA = GUMBO_TAG_TEXTAREA,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/keygen
  KEYGEN = GUMBO_TAG_KEYGEN,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/output
  OUTPUT = GUMBO_TAG_OUTPUT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/progress
  PROGRESS = GUMBO_TAG_PROGRESS,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/meter
  METER = GUMBO_TAG_METER,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/details
  DETAILS = GUMBO_TAG_DETAILS,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/summary
  SUMMARY = GUMBO_TAG_SUMMARY,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/menu
  MENU = GUMBO_TAG_MENU,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/menuitem
  MENUITEM = GUMBO_TAG_MENUITEM,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/applet
  APPLET = GUMBO_TAG_APPLET,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/acronym
  ACRONYM = GUMBO_TAG_ACRONYM,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/bgsound
  BGSOUND = GUMBO_TAG_BGSOUND,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/dir
  DIR = GUMBO_TAG_DIR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/frame
  FRAME = GUMBO_TAG_FRAME,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/frameset
  FRAMESET = GUMBO_TAG_FRAMESET,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/noframes
  NOFRAMES = GUMBO_TAG_NOFRAMES,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/isindex
  ISINDEX = GUMBO_TAG_ISINDEX,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/listing
  LISTING = GUMBO_TAG_LISTING,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/xmp
  XMP = GUMBO_TAG_XMP,
  /// https://developer.mozilla.org/en-US/docs/Web/API/HTMLUnknownElement
  NEXTID = GUMBO_TAG_NEXTID,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/noembed
  NOEMBED = GUMBO_TAG_NOEMBED,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/plaintext
  PLAINTEXT = GUMBO_TAG_PLAINTEXT,
  /// https://developer.mozilla.org/en-US/docs/Web/API/HTMLUnknownElement
  RB = GUMBO_TAG_RB,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/strike
  STRIKE = GUMBO_TAG_STRIKE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/basefont
  BASEFONT = GUMBO_TAG_BASEFONT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/big
  BIG = GUMBO_TAG_BIG,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/blink
  BLINK = GUMBO_TAG_BLINK,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/center
  CENTER = GUMBO_TAG_CENTER,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/font
  FONT = GUMBO_TAG_FONT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/marquee
  MARQUEE = GUMBO_TAG_MARQUEE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/multicol
  MULTICOL = GUMBO_TAG_MULTICOL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/nobr
  NOBR = GUMBO_TAG_NOBR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/spacer
  SPACER = GUMBO_TAG_SPACER,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/tt
  TT = GUMBO_TAG_TT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/rtc
  RTC = GUMBO_TAG_RTC,
  /// Unknown (i.e. non-standard) tag
  UNKNOWN = GUMBO_TAG_UNKNOWN,

  /// Any html tag.
  ANY = 512 // leave room for future html tags
};


} // namespace hext


#endif // HEXT_HTML_TAG_H_INCLUDED


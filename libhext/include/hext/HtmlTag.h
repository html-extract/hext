// Copyright 2015, 2016 Thomas Trapp
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


namespace hext {


/// An enum containing all valid HTML tags.
/// With the exception of HtmlTag::ANY, every HtmlTag can be casted to its
/// GumboTag counterpart (same int value).
enum class HtmlTag : int
{
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/html
  HTML,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/head
  HEAD,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/title
  TITLE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/base
  BASE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/link
  LINK,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/meta
  META,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/style
  STYLE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/script
  SCRIPT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/noscript
  NOSCRIPT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/template
  TEMPLATE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/body
  BODY,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/article
  ARTICLE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/section
  SECTION,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/nav
  NAV,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/aside
  ASIDE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/h1
  H1,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/h2
  H2,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/h3
  H3,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/h4
  H4,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/h5
  H5,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/h6
  H6,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/hgroup
  HGROUP,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/header
  HEADER,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/footer
  FOOTER,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/address
  ADDRESS,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/p
  P,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/hr
  HR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/pre
  PRE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/blockquote
  BLOCKQUOTE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/ol
  OL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/ul
  UL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/li
  LI,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/dl
  DL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/dt
  DT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/dd
  DD,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/figure
  FIGURE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/figcaption
  FIGCAPTION,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/main
  MAIN,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/div
  DIV,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/a
  A,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/em
  EM,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/strong
  STRONG,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/small
  SMALL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/s
  S,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/cite
  CITE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/q
  Q,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/dfn
  DFN,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/abbr
  ABBR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/data
  DATA,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/time
  TIME,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/code
  CODE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/var
  VAR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/samp
  SAMP,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/kbd
  KBD,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/sub
  SUB,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/sup
  SUP,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/i
  I,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/b
  B,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/u
  U,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/mark
  MARK,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/ruby
  RUBY,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/rt
  RT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/rp
  RP,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/bdi
  BDI,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/bdo
  BDO,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/span
  SPAN,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/br
  BR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/wbr
  WBR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/ins
  INS,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/del
  DEL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/image
  IMAGE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/img
  IMG,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/iframe
  IFRAME,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/embed
  EMBED,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/object
  OBJECT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/param
  PARAM,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/video
  VIDEO,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/audio
  AUDIO,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/source
  SOURCE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/track
  TRACK,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/canvas
  CANVAS,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/map
  MAP,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/area
  AREA,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/math
  MATH,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/mi
  MI,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/mo
  MO,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/mn
  MN,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/ms
  MS,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/mtext
  MTEXT,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/mglyph
  MGLYPH,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element
  MALIGNMARK,
  /// https://developer.mozilla.org/en-US/docs/Web/MathML/Element/semantics
  ANNOTATION_XML,
  /// https://developer.mozilla.org/en-US/docs/Web/SVG/Element/svg
  SVG,
  /// https://developer.mozilla.org/en-US/docs/Web/SVG/Element/foreignObject
  FOREIGNOBJECT,
  /// https://developer.mozilla.org/en-US/docs/Web/SVG/Element/desc
  DESC,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/table
  TABLE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/caption
  CAPTION,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/colgroup
  COLGROUP,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/col
  COL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/tbody
  TBODY,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/thead
  THEAD,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/tfoot
  TFOOT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/tr
  TR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/td
  TD,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/th
  TH,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/form
  FORM,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/fieldset
  FIELDSET,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/legend
  LEGEND,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/label
  LABEL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/input
  INPUT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/button
  BUTTON,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/select
  SELECT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/datalist
  DATALIST,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/optgroup
  OPTGROUP,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/option
  OPTION,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/textarea
  TEXTAREA,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/keygen
  KEYGEN,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/output
  OUTPUT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/progress
  PROGRESS,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/meter
  METER,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/details
  DETAILS,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/summary
  SUMMARY,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/menu
  MENU,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/menuitem
  MENUITEM,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/applet
  APPLET,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/acronym
  ACRONYM,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/bgsound
  BGSOUND,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/dir
  DIR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/frame
  FRAME,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/frameset
  FRAMESET,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/noframes
  NOFRAMES,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/isindex
  ISINDEX,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/listing
  LISTING,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/xmp
  XMP,
  /// https://developer.mozilla.org/en-US/docs/Web/API/HTMLUnknownElement
  NEXTID,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/noembed
  NOEMBED,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/plaintext
  PLAINTEXT,
  /// https://developer.mozilla.org/en-US/docs/Web/API/HTMLUnknownElement
  RB,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/strike
  STRIKE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/basefont
  BASEFONT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/big
  BIG,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/blink
  BLINK,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/center
  CENTER,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/font
  FONT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/marquee
  MARQUEE,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/multicol
  MULTICOL,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/nobr
  NOBR,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/spacer
  SPACER,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/tt
  TT,
  /// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/rtc
  RTC,

  /// Any html tag.
  ANY = 512 // leave room for future html tags
};


} // namespace hext


#endif // HEXT_HTML_TAG_H_INCLUDED


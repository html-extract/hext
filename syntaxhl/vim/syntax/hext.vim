" hext syntax highlighting for vim

if exists("b:current_syntax")
  finish
endif

" Comment
syntax match hextComment "\v#.*$"
highlight link hextComment Comment

" Open and closing brackets
syntax match hextRule "\v(\<|\>)"
highlight link hextRule Identifier

" Optional and greedy
syntax match hextSpecial "\v(\?|\+)"
highlight link hextSpecial Special

" Allowed html tags. Taken from gumbo's tag_strings.h.
" Handy one liner:
"   grep -v annotation-xml tag_strings.h \
"     | awk -F\" '{ printf $2 \" \" ; }' \
"     | fold -s -w 60                    \
"     | xargs -L1 -I % echo syn keyword hextTag %
syn case ignore
syn keyword hextTag html head title base link meta style script noscript
syn keyword hextTag template body article section nav aside h1 h2 h3 h4 h5 h6
syn keyword hextTag hgroup header footer address p hr pre blockquote ol ul li
syn keyword hextTag dl dt dd figure figcaption main div a em strong small s
syn keyword hextTag cite q dfn abbr data time code var samp kbd sub sup i b u
syn keyword hextTag mark ruby rt rp bdi bdo span br wbr ins del image img
syn keyword hextTag iframe embed object param video audio source track canvas
syn keyword hextTag map area math mi mo mn ms mtext mglyph malignmark svg
syn keyword hextTag foreignobject desc table caption colgroup col tbody thead
syn keyword hextTag tfoot tr td th form fieldset legend label input button
syn keyword hextTag select datalist optgroup option textarea keygen output
syn keyword hextTag progress meter details summary menu menuitem applet acronym
syn keyword hextTag bgsound dir frame frameset noframes isindex listing xmp
syn keyword hextTag nextid noembed plaintext rb strike basefont big blink
syn keyword hextTag center font marquee multicol nobr spacer tt rtc
syn case match
highlight link hextTag Statement

" Attribute name
syntax match hextAttributeName "\v [a-zA-Z][a-zA-Z0-9\-_]*"
highlight link hextAttributeName Type

" Literal attribute value
syntax region hextLiteral start=/\v"/ skip=/\v\\"/ end=/\v"/
highlight link hextLiteral String

" Literal attribute value with single quotes
syntax region hextLiteral start=/\v'/ skip=/\v\\'/ end=/\v'/
highlight link hextLiteral String

" Builtin attribute name
syntax match hextBuiltin "\v\@[a-z0-9\-_]+"
highlight link hextBuiltin Type

let b:current_syntax = "hext"


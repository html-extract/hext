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

" Direct descendant and optional
syntax match hextSpecial "\v(!|\?)"
highlight link hextSpecial Special

" BUG: In hext, a tag name may be preceded by a number, which is then
" considered as a part of the word that follows, in this case a hextTag, and
" therefore the keyword match fails. But this will not be the case in the
" future, when pseudo-classes are implemented.

" Allowed html tags. Taken from gumbo's tag_strings.h.
" Handy one liner:
"   grep -v annotation-xml tag_strings.h \
"     | awk -F\" '{ printf $2 \" \" ; }' \
"     | fold -s -w 60                    \
"     | xargs -L1 -I % echo syn keyword hextTag %
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
highlight link hextTag Statement

" nth-child
syntax match hextNthChild "\v[0-9]+"
highlight link hextNthChild HtmlTagName

" Attribute name
syntax match hextAttributeName "\v \w+"
highlight link hextAttributeName Normal

" Literal attibute value
syntax region hextLiteral start=/\v"/ skip=/\v\\"/ end=/\v"/
highlight link hextLiteral String

" Capture attribute value
syntax region hextCapture start=/{/ skip=/\/[^/]*\// end=/}/ contains=hextRegex
highlight link hextCapture Special

" Regex attribute value
syntax region hextRegex start=/\v\// skip=/\v\\\// end=/\v\//
highlight link hextRegex Structure

" Builtin attribute name
syntax match hextBuiltin "\v\@[a-z0-9\-_]*"
highlight link hextBuiltin PreProc

let b:current_syntax = "hext"

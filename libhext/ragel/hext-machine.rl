%%{
# Copyright 2015 Thomas Trapp
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


# This ragel machine parses/lexes hext. It is embedded in ragel/Parser.cpp.rl.
machine hext;


#### HELPERS ###################################################################
# Set an attribute capture to optional. By default, attribute captures are
# mandatory, i.e. the attribute has to exist in a node for it to match.
optional = (
  '?' %{ pv.optional = true; }
);
# Negate a match pattern, e.g. style!, class="menu"!, @text=~/foo/!
negate = (
  '!' %{ pv.set_test<NegateTest>(std::move(pv.test)); }
);
# The name of an HTML-element's attribute
attr_name = (
  ( alpha (alnum | '-' | '_')** )
  >{ tk_start(); }
  %{ tk_stop(); pv.attr_name = tok; }
);
# Quoted literal value that may be empty, i.e. "value" or 'value'
opt_quoted =
( '"' (
    ( [^"] | '\\"' )**
    >{ tk_start(); } %{ tk_stop(); pv.literal_value = tok; }
  ) '"' )
|
( '\'' (
    ( [^'] | '\\\'' )**
    >{ tk_start(); } %{ tk_stop(); pv.literal_value = tok; }
  ) '\'' );
# Quoted literal value that may not be empty, i.e. "value" or 'value'
quoted =
( '"' (
    ( ([^"] | '\\"')+ )**
    >{ tk_start(); } %{ tk_stop(); pv.literal_value = tok; }
  ) '"' )
|
( '\'' (
    ( ([^'] | '\\\'')+ )**
    >{ tk_start(); } %{ tk_stop(); pv.literal_value = tok; }
  ) '\'' );


#### NTH_PATTERN ###############################################################
# nth_pattern is used by traits, e.g. nth-last-child(nth_pattern).
# Examples: :nth-child(1)  :nth-child(even)  :nth-child(2n)  :nth-child(2n+1)
nth_pattern = (
  ( 'even' %{ pv.nth = {2, 0}; } )
  |

  ( 'odd' %{ pv.nth = {2, 1}; } )
  |

  ( ( ( '-'? [0-9]+ )
      >{ tk_start(); }
      %{ tk_stop(); pv.nth = {0, std::stoi(tok)}; }
    )
    ( 'n'
      %{ pv.nth = {pv.nth.second, 0}; }
      ( ( ('+'|'-') [0-9]+ )
        >{ tk_start(); }
        %{ tk_stop(); pv.nth.second = std::stoi(tok); }
      )?
    )?
  )
);


#### TRAITS ####################################################################
trait = ':' (
  ( 'empty' %{ pv.set_trait<ChildCountMatch>(0); } )
  |

  ( 'child-count('
    ( [0-9]+
      >{ tk_start(); }
      %{ tk_stop(); pv.set_trait<ChildCountMatch>(std::stoi(tok)); } )
    ')' )
  |

  ( 'attribute-count('
    ( [0-9]+
      >{ tk_start(); }
      %{ tk_stop(); pv.set_trait<AttributeCountMatch>(std::stoi(tok)); } )
    ')' )
  |

  ( 'nth-child(' nth_pattern ')'
    %{ pv.set_trait<NthChildMatch>(pv.nth); } )
  |

  ( 'nth-last-child(' nth_pattern ')'
    %{ pv.set_trait<NthChildMatch>(pv.nth, NthChildMatch::Last); } )
  |

  ( 'nth-of-type(' nth_pattern ')'
    %{ pv.set_trait<NthChildMatch>(pv.nth, NthChildMatch::First|NthChildMatch::OfType); } )
  |

  ( 'first-child'
    %{ pv.set_trait<NthChildMatch>(0, 1); } )
  |

  ( 'first-of-type'
    %{ pv.set_trait<NthChildMatch>(0, 1, NthChildMatch::First|NthChildMatch::OfType); } )
  |

  ( 'last-child'
    %{ pv.set_trait<NthChildMatch>(0, 1, NthChildMatch::Last); } )
  |

  ( 'last-of-type'
    %{ pv.set_trait<NthChildMatch>(0, 1, NthChildMatch::Last|NthChildMatch::OfType); } )
  |

  ( 'nth-last-of-type(' nth_pattern ')'
    %{ pv.set_trait<NthChildMatch>(pv.nth, NthChildMatch::Last|NthChildMatch::OfType); } )
  |

  ( 'only-child' %{ pv.set_trait<OnlyChildMatch>(); } )
  |

  ( 'only-of-type' %{ pv.set_trait<OnlyChildMatch>(OnlyChildMatch::OfType); } )
);
not_trait =
':not('
  %{ pv.negate = std::make_unique<NegateMatch>(); }
  (
    trait
    %{
       assert(pv.negate);
       pv.negate->append_match(std::move(pv.trait));
     }
  )+
')';


#### REGULAR EXPRESSIONS #######################################################
regex = (
  ( '/' ( ( [^/] | '\\/' )** >{ tk_start(); } %{ tk_stop(); } ) '/' )
  |
  ( "'" ( ( [^'] | "\\'" )** >{ tk_start(); } %{ tk_stop(); } ) "'" )
  |
  ( '"' ( ( [^"] | '\\"' )** >{ tk_start(); } %{ tk_stop(); } ) '"' )
)
# regex flags
(
  # case insensitive
  ( 'i' %{ pv.regex_flag |= boost::regex::icase; } )
  |
  # collate (locale aware character groups)
  ( 'c' %{ pv.regex_flag |= boost::regex::collate; } )
)*
%{ try {
     pv.regex = boost::regex(tok, pv.regex_flag);
   }
   catch( const boost::regex_error& e ) {
     // Mark whole regex as error, including slashes and flags
     auto mark_len = static_cast<std::size_t>(this->p - tok_begin + 1);
     this->throw_regex_error(mark_len, e.code());
   }
};
# Wrap a regular expression into a RegexTest.
regex_test = regex %{ assert(pv.regex); pv.set_test<RegexTest>(*pv.regex); };


#### BUILTIN FUNCTION ##########################################################
builtin = (
  '@'
  ( ( 'text'       %{ pv.builtin = TextBuiltin; } )
    |
    ( 'inner-html' %{ pv.builtin = InnerHtmlBuiltin; } )
    |
    ( 'strip-tags' %{ pv.builtin = StripTagsBuiltin; } ) )
);


#### CAPTURE ###################################################################
# captures can be passed through StringPipes, e.g. id:trim:id
pipe = (
  ':'
  ( ( ( 'trim' )                %{ pv.add_pipe<TrimPipe>(); } )
    |
    ( ( 'trim(' quoted ')' )    %{ pv.add_pipe<TrimPipe>(pv.literal_value); } )
    |
    ( ( 'collapsews' )          %{ pv.add_pipe<CollapseWsPipe>(); } )
    |
    ( ( 'tolower' )             %{ pv.add_pipe<CasePipe>(); } )
    |
    ( ( 'toupper' )             %{ pv.add_pipe<CasePipe>(CasePipe::ToUpper); } )
    |
    ( ( 'prepend(' quoted ')' ) %{ pv.add_pipe<PrependPipe>(pv.literal_value); } )
    |
    ( ( 'append(' quoted ')' )  %{ pv.add_pipe<AppendPipe>(pv.literal_value); } )
    |
    ( ( 'filter(' regex ')' )   %{ pv.add_pipe<RegexPipe>(*pv.regex); } )
    |
    ( ( 'replace(' regex space* ',' space* opt_quoted ')' )
        %{ pv.add_pipe<RegexReplacePipe>(*pv.regex, pv.literal_value); } ) )
);
# capture variable, e.g. id:linkid, id:trim:linkid, id:"Menu ID"
capture = (
  pipe* ':'
  (
    ( quoted %{ pv.cap_var = pv.literal_value; } )
    |
    ( (alnum | [\-_.])+ >{ tk_start(); }
                        %{ tk_stop(); pv.cap_var = tok; } ) )
);


#### MATCH_ARG #################################################################
match_arg = (
  ( '=' quoted
    %{ pv.set_test<ContainsWordsTest>(pv.literal_value); } )
  |
  ( '==' opt_quoted
    %{ pv.set_test<EqualsTest>(pv.literal_value); } )
  |
  ( '^=' quoted
    %{ pv.set_test<BeginsWithTest>(pv.literal_value); } )
  |
  ( '*=' quoted
    %{ pv.set_test<ContainsTest>(pv.literal_value); } )
  |
  ( '$=' quoted
    %{ pv.set_test<EndsWithTest>(pv.literal_value); } )
);


#### PATTERNS ##################################################################
pattern = (
  space+
  ( ( ( builtin capture )
      %{ cur_rule().append_capture<FunctionCapture>(
             pv.builtin, pv.cap_var, std::move(pv.pipe)); } )
    |

    ( ( builtin '=~' regex_test negate? )
      %{ cur_rule().append_match<FunctionValueMatch>(pv.builtin, std::move(pv.test)); } )
    |

    ( ( builtin match_arg negate? )
      %{ cur_rule().append_match<FunctionValueMatch>(pv.builtin, std::move(pv.test)); } )
    |

    ( ( attr_name capture optional? )
      %{ cur_rule().append_capture<AttributeCapture>(
             pv.attr_name, pv.cap_var, std::move(pv.pipe));
         if( !pv.optional )
           cur_rule().append_match<AttributeMatch>(pv.attr_name);
       } )
    |

    ( ( attr_name '=~' regex_test negate? )
      %{ cur_rule().append_match<AttributeMatch>(pv.attr_name, std::move(pv.test)); } )
    |

    ( ( attr_name match_arg negate? )
      %{ cur_rule().append_match<AttributeMatch>(pv.attr_name, std::move(pv.test)); } )
    |

    ( ( attr_name
        %{ pv.test = nullptr; }
        negate?
      )
      %{ cur_rule().append_match<AttributeMatch>(pv.attr_name, std::move(pv.test)); } )
  ) %{ pv.reset(); }
);


#### RULES #####################################################################
tag_name = ( alpha (alnum | '-' | '_')** );
main := (
  # ignore whitespace
  space
  |

  # comment
  ( '#' (any - '\n')* '\n' )
  |

  # open rule
  (
    # a rule starts with '<'
    ( '<' %{ push_rule(); } )

    # a rule can have options
    (
      # a rule can be optional
      ( '?' %{ cur_rule().set_optional(true); } )
      |

      # a rule can be greedy
      ( '+' %{ cur_rule().set_greedy(true); } )
    )*

    # a rule must have a tag name, e.g. <div
    ( ( '*' | tag_name ) >{ tk_start(); }
                         %{ tk_stop(); set_open_tag_or_throw(tok); } )

    # a rule can have multiple traits, e.g. :first-child, :empty
    ( ( not_trait %{ cur_rule().append_match(std::move(pv.negate)); } )
      |

      ( trait %{ cur_rule().append_match(std::move(pv.trait)); } ) )*

    # a rule can have multiple match or capture patterns,
    # e.g. class="menu", @text:heading
    pattern*

    space*

    ( ( '/>' %{ pop_rule(); } ) | '>' )
  )
  |

  # end rule
  (
    '</'
    ( ( '*' | tag_name ) >{ tk_start(); }
                         %{ tk_stop();
                            validate_close_tag_or_throw(tok);
                            pop_rule(); } )
    '>'
  )
)* $err{ this->throw_unexpected(); };

}%%

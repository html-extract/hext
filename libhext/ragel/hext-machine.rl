%%{

# This ragel machine parses/lexes hext. It is embedded in ragel/Parser.cpp.rl.
machine hext;


#### NTH_PATTERN ###############################################################
# nth_pattern is used by traits, e.g. nth-last-child(nth_pattern).
# Examples: :nth-child(1)  :nth-child(even)  :nth-child(2n)  :nth-child(2n+1)
nth_pattern = (
  ( 'even' %{ pv.nth = {2, 0}; } )
  |

  ( 'odd' %{ pv.nth = {2, 1}; } )
  |

  ( ( ( '-'? [0-9]+ )
      >{ TK_START; }
      %{ TK_STOP; pv.nth = {0, std::stoi(tok)}; }
    )
    ( 'n'
      %{ pv.nth = {pv.nth.second, 0}; }
      ( ( ('+'|'-') [0-9]+ )
        >{ TK_START; }
        %{ TK_STOP; pv.nth.second = std::stoi(tok); }
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
      >{ TK_START; }
      %{ TK_STOP; pv.set_trait<ChildCountMatch>(std::stoi(tok)); } )
    ')' )
  |

  ( 'attribute-count('
    ( [0-9]+
      >{ TK_START; }
      %{ TK_STOP; pv.set_trait<AttributeCountMatch>(std::stoi(tok)); } )
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
  |

  ( 'text' %{ pv.set_trait<TextNodeMatch>(); } )
);
not_trait =
':not('
  %{ pv.negate = std::make_unique<NegateMatch>(); }
  (
    trait
    %{
       assert(pv.negate);
       pv.negate->take_match(std::move(pv.trait));
     }
  )+
')';


#### REGULAR EXPRESSIONS #######################################################
regex =
'/' ( ( [^/] | '\\/' )** >{ TK_START; } %{ TK_STOP; } ) '/'
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
# capture variable, e.g. id={cap_var}, @text={cap_var}
capture = (
  '{' ( ( [^/{}][^/{}]** )
        >{ TK_START; }
        %{ TK_STOP; pv.cap_var = tok; } )
      # optional capture regex, e.g. @text={time/(\d\d:\d\d)/}
      regex?
  '}'
);


#### HELPERS ###################################################################
# Set an attribute capture to optional. By default, attribute captures are
# mandatory, i.e. the attribute has to exist in a node for it to match.
optional = (
  '?' %{ pv.optional = true; }
);
# Negate a match pattern, e.g. style!, class="menu"!, @text=/foo/!
negate = (
  '!' %{ pv.set_test<NegateTest>(std::move(pv.test)); }
);
# The name of an HTML-element's attribute
attr_name = (
  ( alpha (alnum | '-' | '_')** )
  >{ TK_START; }
  %{ TK_STOP; pv.attr_name = tok; }
);
# Literal value, e.g. attr="literal", class='single'
literal_value =
( '"' (
    ( [^"] | '\\"' )**
    >{ TK_START; } %{ TK_STOP; pv.literal_value = tok; }
  ) '"' )
|
( '\'' (
    ( [^'] | '\\\'' )**
    >{ TK_START; } %{ TK_STOP; pv.literal_value = tok; }
  ) '\'' );


#### LITERAL ###################################################################
literal = (
  ( '=' literal_value
    %{ pv.set_test<ContainsWordsTest>(pv.literal_value); } )
  |
  ( '==' literal_value
    %{ pv.set_test<EqualsTest>(pv.literal_value); } )
  |
  ( '^=' literal_value
    %{ pv.set_test<BeginsWithTest>(pv.literal_value); } )
  |
  ( '*=' literal_value
    %{ pv.set_test<ContainsTest>(pv.literal_value); } )
  |
  ( '$=' literal_value
    %{ pv.set_test<EndsWithTest>(pv.literal_value); } )
);


#### PATTERNS ##################################################################
pattern = (
  space+
  ( ( ( builtin '=' capture )
      %{ if( pv.regex )
           cur_rule().append_capture<FunctionCapture>(pv.builtin, pv.cap_var, *pv.regex);
         else
           cur_rule().append_capture<FunctionCapture>(pv.builtin, pv.cap_var); } )
    |

    ( ( builtin '=' regex_test negate? )
      %{ cur_rule().append_match<FunctionValueMatch>(pv.builtin, std::move(pv.test)); } )
    |

    ( ( builtin literal negate? )
      %{ cur_rule().append_match<FunctionValueMatch>(pv.builtin, std::move(pv.test)); } )
    |

    ( ( attr_name '=' capture optional? )
      %{ if( pv.regex )
           cur_rule()
             .append_capture<AttributeCapture>(pv.attr_name, pv.cap_var, *pv.regex);
         else
           cur_rule().append_capture<AttributeCapture>(pv.attr_name, pv.cap_var);
         if( !pv.optional )
           cur_rule().append_match<AttributeMatch>(pv.attr_name);
       } )
    |

    ( ( attr_name '=' regex_test negate? )
      %{ cur_rule().append_match<AttributeMatch>(pv.attr_name, std::move(pv.test)); } )
    |

    ( ( attr_name literal negate? )
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

    # a rule can be optional, i.e. starts with <?
    ( '?' %{ cur_rule().set_optional(true); } )?

    # a rule must have a tag name, e.g. <div
    ( ('*' | tag_name ) >{ TK_START; }
                        %{ TK_STOP; set_open_tag_or_throw(tok); } )

    # a rule can have multiple traits, e.g. :first-child, :empty
    ( ( not_trait %{ cur_rule().append_match(std::move(pv.negate)); } )
      |

      ( trait %{ cur_rule().append_match(std::move(pv.trait)); } ) )*

    # a rule can have multiple match or capture patterns,
    # e.g. class="menu", @text={heading}
    pattern*

    space*

    ( ( '/>' %{ pop_rule(); } ) | '>' )
  )
  |

  # end rule
  (
    '</'
    ( ( '*' | tag_name ) >{ TK_START; }
                         %{ TK_STOP;
                            validate_close_tag_or_throw(tok);
                            pop_rule(); } )
    '>'
  )
)* $err{ this->throw_unexpected(); };

}%%

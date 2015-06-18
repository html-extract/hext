%%{

# This ragel machine parses/lexes hext. It is embedded in ragel/Parser.cpp.rl.
machine hext;


action error {
  this->throw_unexpected();
}


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
  ( 'empty' %{ pv.push_match<ChildCountMatch>(0); } )
  |

  ( 'child-count('
    ( [0-9]+
      >{ TK_START; }
      %{ TK_STOP; pv.push_match<ChildCountMatch>(std::stoi(tok)); } )
    ')' )
  |

  ( 'attribute-count('
    ( [0-9]+
      >{ TK_START; }
      %{ TK_STOP; pv.push_match<AttributeCountMatch>(std::stoi(tok)); } )
    ')' )
  |

  ( 'nth-child(' nth_pattern ')'
    %{ pv.push_match<NthChildMatch>(pv.nth); } )
  |

  ( 'nth-last-child(' nth_pattern ')'
    %{ pv.push_match<NthChildMatch>(pv.nth, NthOff::Back); } )
  |

  ( 'nth-of-type(' nth_pattern ')'
    %{ pv.push_match<NthChildMatch>(pv.nth, NthOff::Front, rule.tag()); } )
  |

  ( 'first-child'
    %{ pv.push_match<NthChildMatch>(0, 1); } )
  |

  ( 'first-of-type'
    %{ pv.push_match<NthChildMatch>(0, 1, NthOff::Front, rule.tag()); } )
  |

  ( 'last-child'
    %{ pv.push_match<NthChildMatch>(0, 1, NthOff::Back); } )
  |

  ( 'last-of-type'
    %{ pv.push_match<NthChildMatch>(0, 1, NthOff::Back, rule.tag()); } )
  |

  ( 'nth-last-of-type(' nth_pattern ')'
    %{ pv.push_match<NthChildMatch>(pv.nth, NthOff::Back, rule.tag()); } )
  |

  ( 'only-child' %{ pv.push_match<NthChildMatch>(0, 1);
                    pv.push_match<NthChildMatch>(0, 1, NthOff::Back); } )
  |

  ( 'text' %{ pv.push_match<TextNodeMatch>(); } )
);


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
     auto mark_len = this->p - tok_begin + 2;
     this->throw_regex_error(mark_len, e.code());
   }
};
# Wrap a regular expression into a test::Regex.
regex_test = regex %{ assert(pv.regex); pv.set_test<test::Regex>(*pv.regex); };


#### BUILTIN FUNCTION ##########################################################
builtin = (
  '@'
  ( ( 'text'       %{ pv.builtin = GetNodeText; } )
    |
    ( 'inner-html' %{ pv.builtin = GetNodeInnerHtml; } )
    |
    ( 'strip-tags' %{ pv.builtin = StripTagsWrapper; } )
  )
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
  '!' %{ pv.test = MakeUnique<test::Negate>(std::move(pv.test)); }
);
# The name of an HTML-element's attribute
attr_name = (
  ( alpha (alnum | '-' | '_')** )
  >{ TK_START; }
  %{ TK_STOP; pv.attr_name = tok; }
);
# Literal value, e.g. attr="literal"
literal_value = '"' (
  ( [^"] | '\\"' )**
  >{ TK_START; } %{ TK_STOP; pv.literal_value = tok; }
) '"';


#### LITERAL ###################################################################
literal = (
  ( '=' literal_value
    %{ pv.set_test<test::Equals>(pv.literal_value); } )
  |
  ( '^=' literal_value
    %{ pv.set_test<test::BeginsWith>(pv.literal_value); } )
  |
  ( '*=' literal_value
    %{ pv.set_test<test::Contains>(pv.literal_value); } )
  |
  ( '~=' literal_value
    %{ pv.set_test<test::ContainsWord>(pv.literal_value); } )
  |
  ( '$=' literal_value
    %{ pv.set_test<test::EndsWith>(pv.literal_value); } )
);


#### PATTERNS ##################################################################
pattern = (
  space+
  ( ( ( builtin '=' capture )
      %{ pv.push_capture<BuiltinCapture>(pv.cap_var, pv.builtin, pv.regex); } )
    |

    ( ( builtin '=' regex_test negate? )
      %{ pv.push_match<BuiltinMatch>(pv.builtin, std::move(pv.test)); } )
    |

    ( ( builtin literal negate? )
      %{ pv.push_match<BuiltinMatch>(pv.builtin, std::move(pv.test)); } )
    |

    ( ( attr_name '=' capture optional? )
      %{ pv.push_capture<AttributeCapture>(pv.cap_var, pv.attr_name, pv.regex);
         if( !pv.optional )
           pv.push_match<AttributeMatch>(pv.attr_name, MakeUnique<test::True>());
       } )
    |

    ( ( attr_name '=' regex_test negate? )
      %{ pv.push_match<AttributeMatch>(pv.attr_name, std::move(pv.test)); } )
    |

    ( ( attr_name literal negate? )
      %{ pv.push_match<AttributeMatch>(pv.attr_name, std::move(pv.test)); } )
    |

    ( ( attr_name
        %{ pv.set_test<test::True>(); }
        negate?
      )
      %{ pv.push_match<AttributeMatch>(pv.attr_name, std::move(pv.test)); } )
  ) %{ pv.reset(); }
);


#### RULES #####################################################################
tag_name = ( alpha (alnum | '-' | '_')** );
main := (
  # comments may be prefixed with any spaces and must terminate with a newline
  ( ' '* '#' (any - '\n')* '\n' )
  |

  # open rule
  (
    # ignore whitespace
    space*

    # a rule starts with '<'
    '<'

    # a rule can be optional, e.g. <?
    ( '?' %{ rule.set_optional(true); } )?

    # a rule can have a tag name, e.g. <div
    ( tag_name >{ TK_START; }
               %{ TK_STOP;
                  if( !rule.set_tag_name(tok) )
                    this->throw_unknown_token(tok, "html-tag"); }
    )?

    # a rule can have multiple traits, e.g. :first-child, :empty
    trait*

    # a rule can have multiple match or capture patterns,
    # e.g. class="menu", @text={heading}
    pattern*

    space*

    # a rule can be self-closing, e.g. <p/>
    ( '/' %{ rule.set_self_closing(true); } )?

    # a rule definition ends with a '>'
    ( '>' %{ rule.consume_rule(); } )

    space*
  )
  |

  # end rule
  (
    space*

    '</'
    (
      tag_name?
      >{ TK_START; }
      %{ TK_STOP; }
    )
    '>'
    %{ if( !rule.consume_closing_tag(tok) )
         this->throw_expected_closing_tag(tok, rule.expected_closing_tag()); }

    space*
  )
)** $err(error) $/{ fbreak; };

}%%

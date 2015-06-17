%%{
# This ragel machine lexes hext. It is embedded in Parser::parse.
machine hext;

action error {
  this->throw_unexpected();
}

#### HELPERS ###################################################################
attr_name     = ( alpha (alnum | '-' | '_')** );
builtin_name  = ( alpha (alnum | '-' | '_')** );
cap_var       = ( [^/{}][^/{}]** );
match_literal = ( ( [^"] | '\\"' )** );
regex_content = ( ( [^/] | '\\/' )** );


#### NTH_PATTERN ###############################################################
# nth_pattern is used in some traits, e.g. nth-child(nth_pattern).
# Examples: :nth-child(1)  :nth-child(even)  :nth-child(2n)  :nth-child(2n+1)
nth_pattern = (
  # nth-child(even)
  ( 'even' %{ pattern.nth = {2, 0}; } )
  |

  # nth-child(odd)
  ( 'odd' %{ pattern.nth = {2, 1}; } )
  |

  # nth-child(2n+1)
  ( ( ( '-'? [0-9]+ )
      >{ TK_START; }
      %{ TK_STOP; pattern.nth = {std::stoi(tok), 0}; }
    )
    ( 'n'
      ( ( ('+'|'-') [0-9]+ )
        >{ TK_START; }
        %{ TK_STOP; pattern.nth.second = std::stoi(tok); }
      )?
    )?
  )
);


#### TRAITS ####################################################################
trait = ':' (
  # :empty
  ( 'empty' %{ pattern.push_match<ChildCountMatch>(0); } )
  |

  # :attribute-count(5)
  ( 'attribute-count('
    ( [0-9]+
      >{ TK_START; }
      %{ TK_STOP; pattern.push_match<AttributeCountMatch>(std::stoi(tok)); } )
    ')' )
  |

  # :child-count(5)
  ( 'child-count('
    ( [0-9]+
      >{ TK_START; }
      %{ TK_STOP; pattern.push_match<ChildCountMatch>(std::stoi(tok)); } )
    ')' )
  |

  # :nth-child(2n+1)
  ( 'nth-child(' nth_pattern ')' %{ pattern.push_nth_child(); } )
  |

  # :nth-last-child(2n+1)
  ( 'nth-last-child(' nth_pattern ')'
    %{ pattern.push_nth_child(NthOff::Back); } )
  |

  # :nth-of-type(2n+1)
  ( 'nth-of-type(' nth_pattern ')'
    %{ pattern.push_nth_child(NthOff::Front, rule.tag()); } )
  |

  # :first-child
  ( 'first-child' %{ pattern.nth = {1, 0}; pattern.push_nth_child(); } )
  |

  # :first-of-type
  ( 'first-of-type'
    %{ pattern.nth = {1, 0};
       pattern.push_nth_child(NthOff::Front, rule.tag()); } )
  |

  # :last-child
  ( 'last-child'
    %{ pattern.nth = {1, 0}; pattern.push_nth_child(NthOff::Back); } )
  |

  # :last-of-type
  ( 'last-of-type'
    %{ pattern.nth = {1, 0};
       pattern.push_nth_child(NthOff::Back, rule.tag()); } )
  |

  # :nth-last-of-type(2n+1)
  ( 'nth-last-of-type(' nth_pattern ')'
    %{ pattern.push_nth_child(NthOff::Back, rule.tag()); } )
  |

  # :only-child
  ( 'only-child'
    %{ pattern.nth = {1, 0}; pattern.push_nth_child();
       pattern.nth = {1, 0}; pattern.push_nth_child(NthOff::Back); } )
  |

  # :text
  ( 'text'
    %{ pattern.push_match<TextNodeMatch>(); } )
);


# Literal value, e.g. attr="literal"
literal_value = '"' ( match_literal
  >{ TK_START; } %{ TK_STOP; pattern.set_attr_literal(tok); }
) '"';


# Regular expression
regex = '/' ( regex_content
    >{ TK_START; }
    %{ TK_STOP; pattern.set_regex_str(tok); }
  ) '/'
  # regex modifier:
  # 'i': case insensitive
  # 'c': collate (locale aware character groups)
  # Capture all characters to provide better error diagnostics.
  ( [a-zA-Z!]+ )?
  >{ TK_START; }
  %{ TK_STOP;
     if( !pattern.set_regex_mod(tok) )
       this->throw_unknown_token(tok, "regex modifier");
     try{ pattern.consume_regex(); }
     catch( const boost::regex_error& e )
     { // Mark whole regex as error, including slashes
       auto mark_len = pattern.regex_length() + tok.size() + 2;
       this->throw_regex_error(mark_len, e.code()); } };


#### ATTRIBUTES ################################################################
attributes = (
  space+
  (
    # attribute name
    (
      # negate match pattern, e.g. !style="display:none"
      ( '!' >{ pattern.set_negate(); } )?

      (
        # builtin function, e.g. @text
        ( '@'
          ( builtin_name
            >{ TK_START; }
            %{ TK_STOP; { if( !pattern.set_builtin(tok) )
                            this->throw_unknown_token(tok, "builtin"); } } ) )
        |

        # html node attribute, e.g. class
        ( attr_name >{ TK_START; } %{ TK_STOP; pattern.set_attr_name(tok); } )
      )
    )

    # attribute value
    (
      # literal operator, e.g. @text^="Lorem ", class~="menu"
      ( ( '^' | '*' | '~' | '$' ) >{ pattern.set_literal_op(*this->p); }
        '=' literal_value )
      |

      # capture variable, match regex or match literal
      ( '='
        (
          # capture variable, e.g. id={html_node_attr_id}, @text={heading}
          ( '{' cap_var >{ TK_START; }
                %{ TK_STOP; pattern.set_cap_var(tok); }
                # optional capture regex, e.g. @text={time/(\d\d:\d\d)/}
                regex?
            '}'
            ( '?' %{ pattern.set_optional(); } )?
          )
          |

          # match regex, e.g. id=/article_[0-9]+/
          regex
          |

          # match literal, e.g. id="article_23"
          literal_value
        )
      )
    )?
  ) %{ pattern.consume_pattern(); }
)+;


#### RULES #####################################################################
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
    ( attr_name >{ TK_START; }
                %{ TK_STOP;
                   if( !rule.set_tag_name(tok) )
                     this->throw_unknown_token(tok, "html-tag"); }
    )?

    # a rule can have multiple traits, e.g. <div:first-child
    trait*

    # a rule can have multple attributes, e.g. <div class="menu"
    attributes?

    space*

    # a rule can be self-closing, e.g. <p/>
    ( '/' %{ rule.set_self_closing(true); } )?

    # a rule ends with a '>'
    ( '>' %{ rule.consume_rule(); } )

    space*
  )
  |

  # end rule
  (
    space*

    '</'
    (
      attr_name?
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

%%{
# This ragel machine lexes hext. It is embedded in Parser::parse.
machine hext;

action error {
  this->throw_unexpected();
}

action act_newline {
  if( rule_start )
  {
    rule.consume_rule();
    rule_start = false;
  }
  else
  {
    // If a newline is encountered, reset indent, because the spaces could have
    // been used to indent a comment.
    rule.reset_indent();
  }
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
  ( 'even' %{ pattern.set_nth_mul("2"); pattern.set_nth_add("0"); } )
  |

  # nth-child(odd)
  ( 'odd' %{ pattern.set_nth_mul("2"); pattern.set_nth_add("1"); } )
  |

  # nth-child(2n+1)
  ( ( [0-9]+ >{ TK_START; } %{ TK_STOP; pattern.set_nth_mul(tok); } )
    ( 'n'    %{ pattern.set_nth_add("0"); }
      ( '+'
        ( [0-9]+ >{ TK_START; } %{ TK_STOP; pattern.set_nth_add(tok); } )
      )?
    )?
  )
);


#### TRAITS ####################################################################
trait = ':' (
  # :empty
  ( 'empty' %{ pattern.consume_child_count("0"); } )
  |

  # :child-count(5)
  ( 'child-count('
    ( [0-9]+ >{ TK_START; } %{ TK_STOP; pattern.consume_child_count(tok); } )
    ')' )
  |

  # :nth-child(2n+1)
  ( 'nth-child(' nth_pattern ')' %{ pattern.consume_nth_child(); } )
  |

  # :nth-last-child(2n+1)
  ( 'nth-last-child(' nth_pattern ')'
    %{ pattern.consume_nth_child(NthOff::Back); } )
  |

  # :nth-of-type(2n+1)
  ( 'nth-of-type(' nth_pattern ')'
    %{ pattern.consume_nth_child(NthOff::Front, rule.tag()); } )
  |

  # :first-child
  ( 'first-child' %{ pattern.set_nth_mul("1"); pattern.consume_nth_child(); } )
  |

  # :first-of-type
  ( 'first-of-type'
    %{ pattern.set_nth_mul("1");
       pattern.consume_nth_child(NthOff::Front, rule.tag()); } )
  |

  # :last-child
  ( 'last-child'
    %{ pattern.set_nth_mul("1"); pattern.consume_nth_child(NthOff::Back); } )
  |

  # :last-of-type
  ( 'last-of-type'
    %{ pattern.set_nth_mul("1");
       pattern.consume_nth_child(NthOff::Back, rule.tag()); } )
  |

  # :nth-last-of-type(2n+1)
  ( 'nth-last-of-type(' nth_pattern ')'
    %{ pattern.consume_nth_child(NthOff::Back, rule.tag()); } )
  |

  # :only-child
  ( 'only-child'
    %{ pattern.set_nth_mul("1"); pattern.consume_nth_child();
       pattern.set_nth_mul("1"); pattern.consume_nth_child(NthOff::Back); } )
);


# attr="literal"
literal_value = '"' ( match_literal
  >{ TK_START; } %{ TK_STOP; pattern.set_attr_literal(tok); }
) '"';

# regular expression
regex = '/' ( regex_content
    >{ TK_START; }
    %{ TK_STOP; pattern.set_regex_str(tok); }
  ) '/'
  # regex modifier:
  # 'i': case insensitive
  # 'c': collate (locale aware character groups)
  # '!': negate regex
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
  ' '+
  (
    # attribute name
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

    # attribute value
    (
      # literal operator, e.g. @text^="Lorem ", class~="menu"
      ( ( '^' | '*' | '!' | '~' | '$' ) >{ pattern.set_literal_op(*this->p); }
        '=' literal_value )
      |

      # capture variable, match regex or match literal
      ( '='
        (
          # capture variable, e.g. id={html_node_attr_id}, @text={heading}
          ( '{' cap_var >{ TK_START; }
                %{ TK_STOP;
                   if( rule.path() )
                     this->throw_error("Paths cannot have captures", tok.size());
                   pattern.set_cap_var(tok); }
                # optional capture regex, e.g. @text={time/(\d\d:\d\d)/}
                regex?
            '}' )
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
  ( ' '* '#' (any - '\n')* ( '\n' %act_newline ) )
  |

  (
    # groups of two spaces indent a rule
    ( '  ' %{ rule.increment_indent(); } )*

    # a rule starts with either '<' (direct descendant), '>' (any descendant)
    # or '~' (path)
    ( ( ( '<' )
        |
        ( '>' %{ rule.set_any_descendant(true); } )
        |
        ( '~' %{ rule.set_any_descendant(true); rule.set_path(true); } )
      ) %{ rule_start = true; }
    )

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

    # a rule can be closed ("nodes may not have more attributes than specified")
    ( '>' %{ rule.set_closed(true); } )?
  )

  # rules and comments may terminate with a newline
  ( '\n' %act_newline )?
)** $err(error) $/act_newline $/{ fbreak; };

}%%

%%{
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
      rule.reset_indent();
    }
  }

  attr_name = ( alpha (alnum | '-' | '_')** );
  builtin_name = ( alpha (alnum | '-' | '_')** );
  cap_var = ( [^/{}][^/{}]** );
  match_literal = ( [^/{}"][^/{}"]** );
  cap_regex = ( ( [^/] | '\\/' )** );
  match_regex = ( ( [^/] | '\\/' )** );

  comment = (
    ' '*
    '#'
    (any - '\n')*
    (
      '\n' %act_newline
    )
  );


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


  attributes = (
    ' '+
    (
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
            ( '{' cap_var >{ TK_START; } %{ TK_STOP; pattern.set_cap_var(tok); }
              # optional capture regex, e.g. @text={time/(\d\d+:\d+\d+)/}
              ( '/' cap_regex >{ TK_START; }
                              %{ TK_STOP;
                                 try{ pattern.set_cap_regex(tok); }
                                 catch( const boost::regex_error& e )
                                 { this->throw_regex_error(tok, e.code()); } }
                '/'
              )?
              '}' )
            |
            # match regex, e.g. id=/article_[0-9]+/
            ( '/' match_regex >{ TK_START; }
                              %{ TK_STOP;
                                 try{ pattern.set_attr_regex(tok); }
                                 catch( const boost::regex_error& e )
                                 { this->throw_regex_error(tok, e.code()); } }
              '/' )
            |
            # match literal, e.g. id="article_23"
            literal_value
          )
        )
      )?
    ) %{ pattern.consume_pattern(); }
  )+;


  main := 
    ( 
      comment
      |
      (
        (
          '  ' %{ rule.increment_indent(); }
        )*
        (
          (
            '<'
            %{ rule_start = true; }
          )
          |
          (
            '>'
            %{
              rule_start = true;
              rule.set_any_descendant(true);
             }
          )
        )
        (
          '?' %{ rule.set_optional(true); }
        )?
        (
          attr_name >{ TK_START; }
                    %{ TK_STOP;
                       if( !rule.set_tag_name(tok) )
                         this->throw_unknown_token(tok, "html-tag"); }
        )?
        trait*
        attributes?
        (
          '>' %{ rule.set_closed(true); }
        )?
      )
      (
        '\n' %act_newline
      )?
    )**
    $err(error) $/act_newline $/{ fbreak; };
}%%

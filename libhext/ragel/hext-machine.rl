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
    (
      'even'
      %{
        pattern.set_nth_mul("2");
        pattern.set_nth_add("0");
       }
    )
    |
    (
      'odd'
      %{
        pattern.set_nth_mul("2");
        pattern.set_nth_add("1");
       }
    )
    |
    (
      (
        [0-9]+
        >{ TK_START; }
        %{ TK_STOP; pattern.set_nth_mul(tok); }
      )
      (
        'n'
        %{ // '2n' must behave the same as '2n+0'.
           pattern.set_nth_add("0");
         }
        (
          '+'
          (
            [0-9]+
            >{ TK_START; }
            %{ TK_STOP; pattern.set_nth_add(tok); }
          )
        )?
      )?
    )
  );

  trait = (
    ':'
    (
      (
        ( 'empty' )
        %{ pattern.consume_child_count("0"); }
      )
      |
      (
        (
          'child-count('
          (
            [0-9]+
            >{ TK_START; }
            %{ TK_STOP; pattern.consume_child_count(tok); }
          )
          ')'
        )
      )
      |
      (
        ( 'nth-child(' nth_pattern ')' )
        %{ pattern.consume_nth_child(); }
      )
      |
      (
        ( 'nth-last-child(' nth_pattern ')' )
        %{
          pattern.consume_nth_child(NthOff::Back);
         }
      )
      |
      (
        ( 'nth-of-type(' nth_pattern ')' )
        %{
          pattern.consume_nth_child(
            NthOff::Front,
            rule.tag()
          );
         }
      )
      |
      (
        ( 'first-child' )
        %{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child();
         }
      )
      |
      (
        ( 'first-of-type' )
        %{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child(
            NthOff::Front,
            rule.tag()
          );
         }
      )
      |
      (
        ( 'last-child' )
        %{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child(NthOff::Back);
         }
      )
      |
      (
        ( 'last-of-type' )
        %{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child(
            NthOff::Back,
            rule.tag()
          );
         }
      )
      |
      (
        ( 'nth-last-of-type(' nth_pattern ')' )
        %{
          pattern.consume_nth_child(
            NthOff::Back,
            rule.tag()
          );
         }
      )
      |
      (
        ( 'only-child' )
        %{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child();
          pattern.set_nth_mul("1");
          pattern.consume_nth_child(NthOff::Back);
         }
      )
    )
  );

  literal_value = (
    '"'
    (
      match_literal >{ TK_START; }
                    %{ TK_STOP;
                       pattern.set_attr_literal(tok); }
    )
    '"'
  );

  attributes = 
    (
      ' '+
      (
        (
          (
            '@'
            (
              builtin_name
              >{ TK_START; }
              %{ TK_STOP;
                 {
                   if( !pattern.set_builtin(tok) )
                     this->throw_unknown_token(tok, "builtin");
                 }
              }
            )
          )
          |
          (
            attr_name >{ TK_START; }
                      %{ TK_STOP; pattern.set_attr_name(tok); }
          )
        )
        (
          (
            ( '^' | '*' | '!' | '~' | '$' )
            >{ pattern.set_literal_op(*this->p); }
            '=' literal_value
          )
          |
          (
            '='
            (
              (
                '{'
                (
                  cap_var >{ TK_START; }
                          %{ TK_STOP; pattern.set_cap_var(tok); }
                )
                (
                  '/'
                  (
                    cap_regex >{ TK_START; }
                              %{ TK_STOP;
                                 try{ pattern.set_cap_regex(tok); }
                                 catch( const boost::regex_error& e )
                                 { this->throw_regex_error(tok, e.code()); }
                               }
                  )
                  '/'
                )?
                '}'
              )
              |
              (
                (
                  '/'
                  (
                    match_regex >{ TK_START; }
                                %{ TK_STOP;
                                   try{ pattern.set_attr_regex(tok); }
                                   catch( const boost::regex_error& e )
                                   { this->throw_regex_error(tok, e.code()); }
                                 }
                  )
                  '/'
                )
                |
                literal_value
              )
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

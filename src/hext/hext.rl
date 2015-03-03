%%{
  machine hext;

  action error {
    this->throw_unexpected();
  }

  action act_newline {
    if( rule_start )
    {
      rule.consume_and_reset();
      rule_start = false;
    }
    else
    {
      rule.reset_indent();
    }
  }

  nth_child = ( [1-9][0-9]** );
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

  attributes = 
    (
      space+ 
      (
        (
          (
            '@'
            (
              builtin_name
              >{ LX_TK_START; }
              %{ LX_TK_STOP;
                 {
                   if( !rule.pattern().set_builtin_function(tok) )
                     this->throw_unknown_token(tok, "builtin");
                 }
              }
            )
          )
          |
          (
            attr_name >{ LX_TK_START; }
                      %{ LX_TK_STOP; rule.pattern().set_attr_name(tok); }
          )
        )
        (
          '='
          (
            (
              '{'
              (
                cap_var >{ LX_TK_START; }
                        %{ LX_TK_STOP; rule.pattern().set_cap_var(tok); }
              )
              (
                '/'
                (
                  cap_regex >{ LX_TK_START; }
                            %{ LX_TK_STOP;
                               try{ rule.pattern().set_cap_regex(tok); }
                               catch( const boost::regex_error& e )
                               { this->throw_regex_error(tok, e); }
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
                  match_regex >{ LX_TK_START; }
                              %{ LX_TK_STOP;
                                 try{ rule.pattern().set_attr_regex(tok); }
                                 catch( const boost::regex_error& e )
                                 { this->throw_regex_error(tok, e); }
                               }
                )
                '/'
              )
              |
              (
                '"'
                (
                  match_literal >{ LX_TK_START; }
                                %{ LX_TK_STOP;
                                   rule.pattern().set_attr_literal(tok); }
                )
                '"'
              )
            )
          )
        )?
      ) %{ rule.pattern().consume_and_reset(); }
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
          '<' %{ rule_start = true; }
        )
        (
          '?' %{ rule.set_optional(true); }
        )?
        (
          (
            '!' %{ rule.set_nth_child(0); }
          )
          |
          (
            nth_child >{ LX_TK_START; }
                      %{ LX_TK_STOP;
                         rule.set_nth_child(std::stoi(tok)); }
          )
        )?
        (
          attr_name >{ LX_TK_START; }
                    %{ LX_TK_STOP;
                       if( !rule.set_tag_name(tok) )
                         this->throw_unknown_token(tok, "html-tag"); }
        )?
        attributes?
        (
          '>' %{ rule.set_closed(true); }
        )?
      ):>
      (
        '\n' %act_newline
      )
    )**
    $err(error) $/act_newline $/{ fbreak; };
}%%

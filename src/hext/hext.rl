%%{
  machine hext;

  action error {
    print_error();
    throw lex_error("syntax error");
  }

  cap_limit = ( '*' | [1-9][0-9]** );
  attr_name = ( alpha (alnum | '-' | '_')** );
  attr_value = ( alpha (alnum | '-' | '_')** );

  attributes = 
    (
      space+ 
      (
        (
          attr_name >{ LX_TK_START(TK_ATTR_NAME); }
                    %{ LX_TK_STOP; }
        )
        <:
        (
          '="'
          (
            (
              '(:'
              (
                attr_value** >{ LX_TK_START(TK_ATTR_CAPTURE); }
                             %{ LX_TK_STOP; }
              )
              ')'
            )
            |
            (
              attr_value** >{ LX_TK_START(TK_ATTR_LITERAL); }
                           %{ LX_TK_STOP; }
            )
          )
          '"'
        )?
      )
    )+;

  main := 
    ( 
      (
        '  ' >{ LX_TK_START(TK_INDENT); }
             %{ LX_TK_STOP; }
      )*
      ( 
        '<' >{ LX_TK_START(TK_RULE_BEGIN); } 
            %{ LX_TK_STOP; }
      )
      (
        '!' >{ LX_TK_START(TK_DIRECT_DESC); } 
            %{ LX_TK_STOP; }
      )?
      (
        cap_limit >{ LX_TK_START(TK_CAP_LIMIT); } 
                  %{ LX_TK_STOP; }
      )?
      ( 
        attr_name >{ LX_TK_START(TK_TAG_NAME); }
                  %{ LX_TK_STOP; }
      )?
      attributes?
      (
        '>' >{ LX_TK_START(TK_RULE_END); } 
            %{ LX_TK_STOP; }
      )
      '\n'
    )**
    $err(error) $/{ LX_TK_START(TK_EOF); fbreak; };
}%%

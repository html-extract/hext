%%{
  machine hext;

  action error {
    throw_error();
  }

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

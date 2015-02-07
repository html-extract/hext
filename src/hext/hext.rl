%%{
  machine hext;

  action error {
    throw_error();
  }

  nth_child = ( [1-9][0-9]** );
  attr_name = ( alpha (alnum | '-' | '_')** );
  cap_var       = ( [^/{}][^/{}]** );
  match_literal = ( [^/{}"][^/{}"]** );
  cap_regex   = ( ( [^/] | '\\/' )** );
  match_regex = ( ( [^/] | '\\/' )** );

  comment = (
    ' '*
    '#'
    (any - '\n')*
    (
      '\n' >{ LX_TK_START(TK_NEWLINE); }
           %{ LX_TK_STOP; }
    )
  );

  attributes = 
    (
      space+ 
      (
        (
          '@' >{ LX_TK_START(TK_BUILTIN); }
              %{ LX_TK_STOP; }
        )?
        (
          attr_name >{ LX_TK_START(TK_ATTR_NAME); }
                    %{ LX_TK_STOP; }
        )
        <:
        (
          '='
          (
            (
              (
                '{' >{ LX_TK_START(TK_CAP_BEGIN); }
                    %{ LX_TK_STOP; }
              )
              (
                cap_var >{ LX_TK_START(TK_CAP_VAR); }
                        %{ LX_TK_STOP; }
              )
              (
                '/'
                (
                  cap_regex >{ LX_TK_START(TK_CAP_REGEX); }
                            %{ LX_TK_STOP; }
                )
                '/'
              )?
              (
                '}' >{ LX_TK_START(TK_CAP_END); }
                    %{ LX_TK_STOP; }
              )
            )
            |
            (
              (
                '/'
                (
                  match_regex >{ LX_TK_START(TK_MATCH_REGEX); }
                              %{ LX_TK_STOP; }
                )
                '/'
              )
              |
              (
                '"'
                (
                  match_literal >{ LX_TK_START(TK_MATCH_LITERAL); }
                                %{ LX_TK_STOP; }
                )
                '"'
              )
            )
          )
        )?
      )
    )+;

  main := 
    ( 
      comment
      |
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
          nth_child >{ LX_TK_START(TK_NTH_CHILD); }
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
        )?
      ):>
      (
        '\n' >{ LX_TK_START(TK_NEWLINE); }
             %{ LX_TK_STOP; }
      )
    )**
    $err(error) $/{ LX_TK_START(TK_EOF); fbreak; };
}%%

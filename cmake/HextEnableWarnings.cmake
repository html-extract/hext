# Enable reasonable warnings.

# Clang
IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  ADD_DEFINITIONS("-Weverything" "-Wno-c++98-compat" "-Wno-padded"
    "-Wno-documentation-unknown-command" "-Wno-documentation-html"
    "-Wno-documentation" "-Wno-weak-vtables" "-Wno-switch-enum"
    "-Wno-exit-time-destructors" "-Wno-global-constructors")
ENDIF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

# G++
IF(CMAKE_COMPILER_IS_GNUCXX)
  ADD_DEFINITIONS(
    "-pedantic" "-pedantic-errors" "-Wall" "-Wcast-align" "-Wcast-qual"
    "-Wchar-subscripts" "-Wcomment" "-Wconversion" "-Wctor-dtor-privacy"
    "-Wdisabled-optimization" "-Weffc++" "-Wextra" "-Wfloat-equal"
    "-Wformat=2" "-Wformat-nonliteral" "-Wformat-security" "-Wformat-y2k"
    "-Wimport" "-Winit-self" "-Winvalid-pch" "-Wlogical-op"
    "-Wlong-long" "-Wmissing-braces" "-Wmissing-field-initializers"
    "-Wmissing-format-attribute" "-Wmissing-include-dirs"
    "-Woverloaded-virtual" "-Wpacked" "-Wparentheses" "-Wpointer-arith"
    "-Wredundant-decls" "-Wreturn-type" "-Wsequence-point" "-Wshadow"
    "-Wsign-compare" "-Wsign-promo" "-Wstack-protector" "-Wstrict-aliasing=2"
    "-Wstrict-null-sentinel" "-Wstrict-overflow" "-Wswitch"
    "-Wtrigraphs" "-Wundef" "-Wuninitialized" "-Wunknown-pragmas"
    "-Wunreachable-code" "-Wunused"
    "-Wunused-function" "-Wunused-label" "-Wunused-parameter" "-Wunused-value"
    "-Wunused-variable" "-Wvariadic-macros" "-Wvolatile-register-var"
    "-Wwrite-strings" "-Wmissing-noreturn" "-Wsign-conversion"
    # Unused switches:
    # "-Wswitch-enum": Listing every enum brings chaos, especially for GumboTag.
    # "-Wswitch-default": generated ragel code uses switch without default,
    #                     we cannot do anything about that
    # "-Wpadded": also warns when it's impossible to shrink padding
    # "-Wunsafe-loop-optimizations":
    #   GCC7 will emit warnings when using range-based for loops:
    #     "warning: missed loop optimization, the loop counter may overflow"
    #   Since it's only complaining about a missed optimization, this warning
    #   can safely be disabled.
  )
ENDIF(CMAKE_COMPILER_IS_GNUCXX)


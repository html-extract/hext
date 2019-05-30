# Enable reasonable warnings.

# Clang
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_definitions("-Weverything" "-Wno-c++98-compat" "-Wno-padded"
    "-Wno-documentation-unknown-command" "-Wno-documentation-html"
    "-Wno-documentation" "-Wno-weak-vtables" "-Wno-switch-enum"
    "-Wno-exit-time-destructors" "-Wno-global-constructors")
endif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

# G++
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_definitions(
    "-Wall"
    "-Wcast-align"
    "-Wcast-qual"
    "-Wconversion"
    "-Wctor-dtor-privacy"
    "-Wdisabled-optimization"
    "-Weffc++"
    "-Wextra"
    "-Wfloat-equal"
    "-Wformat=2"
    "-Wimport"
    "-Winvalid-pch"
    "-Wlogical-op"
    "-Wlong-long"
    "-Wmissing-format-attribute"
    "-Wmissing-include-dirs"
    "-Wmissing-noreturn"
    "-Woverloaded-virtual"
    "-Wpacked"
    "-Wpointer-arith"
    "-Wredundant-decls"
    "-Wshadow"
    "-Wsign-conversion"
    "-Wsign-promo"
    "-Wstack-protector"
    "-Wstrict-aliasing=2"
    "-Wstrict-null-sentinel"
    "-Wstrict-overflow"
    "-Wswitch"
    "-Wundef"
    "-Wunreachable-code"
    "-Wunused"
    "-Wvariadic-macros"
    "-Wwrite-strings"
    "-pedantic"
    "-pedantic-errors"
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
endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")


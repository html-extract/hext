function(hext_enable_warnings_gnu)
  target_compile_options(
    ${ARGN}
    "-Wall"
    "-Wcast-align=strict"
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
    "-Wformat-overflow=2"
    "-Wformat-truncation=2"
    "-Wreturn-local-addr"
    "-Warith-conversion"
    "-Wstringop-overflow=4"
    "-Wmismatched-tags"
    "-Wredundant-tags"
    "-Wsuggest-override"
    "-Wctad-maybe-unsupported"
    "-Wdeprecated-enum-enum-conversion"
    "-Wdeprecated-enum-float-conversion"
    "-Wunsafe-loop-optimizations"
    "-Wswitch-default"
    "-Wswitch-enum"
    # Unused switches:
    # "-Wpadded": also warns when it's impossible to shrink padding
    # Notes:
    # "-Wunsafe-loop-optimizations":
    #   GCC7 will emit warnings when using range-based for loops:
    #     "warning: missed loop optimization, the loop counter may overflow"
    #   Since it's only complaining about a missed optimization, this warning
    #   can safely be ignored.
  )
endfunction()

function(hext_enable_warnings_clang)
  target_compile_options(
    ${ARGN}
    "-Weverything"
    "-Wno-c++98-compat"
    "-Wno-c++98-compat-pedantic"
    "-Wno-documentation"
    "-Wno-documentation-html"
    "-Wno-documentation-unknown-command"
    "-Wno-exit-time-destructors"
    "-Wno-global-constructors"
    "-Wno-padded"
    "-Wno-switch-enum"
    "-Wno-covered-switch-default"
    "-Wno-weak-vtables")
endfunction()

function(hext_enable_warnings)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    hext_enable_warnings_clang(${ARGN})
  endif()

  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    hext_enable_warnings_gnu(${ARGN})
  endif()
endfunction()


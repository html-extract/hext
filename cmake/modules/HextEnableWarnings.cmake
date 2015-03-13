# Enable all (reasonable) warnings, depending on compiler. The only compilers covered
# are Clang and GCC.

# Clang
IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  ADD_DEFINITIONS("-Weverything")
ENDIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

# G++
IF(CMAKE_COMPILER_IS_GNUCXX)
  ADD_DEFINITIONS(
    "-pedantic" "-pedantic-errors" "-Wall" "-Wcast-align" "-Wcast-qual"
    "-Wchar-subscripts" "-Wcomment" "-Wconversion" "-Wctor-dtor-privacy"
    "-Wdisabled-optimization" "-Weffc++" "-Wextra" "-Wfloat-equal"
    "-Wformat=2" "-Wformat-nonliteral" "-Wformat-security" "-Wformat-y2k"
    "-Wimport" "-Winit-self" "-Winvalid-pch" "-Wlogical-op"
    "-Wlong-long" "-Wmissing-braces" "-Wmissing-field-initializers"
    "-Wmissing-format-attribute" "-Wmissing-include-dirs" "-Wno-unused"
    "-Woverloaded-virtual" "-Wpacked" "-Wparentheses" "-Wpointer-arith"
    "-Wredundant-decls" "-Wreturn-type" "-Wsequence-point" "-Wshadow"
    "-Wsign-compare" "-Wsign-promo" "-Wstack-protector" "-Wstrict-aliasing=2"
    "-Wstrict-null-sentinel" "-Wstrict-overflow=5" "-Wswitch" "-Wswitch-enum"
    "-Wtrigraphs" "-Wundef" "-Wuninitialized" "-Wunknown-pragmas"
    "-Wunreachable-code" "-Wunused"
    "-Wunused-function" "-Wunused-label" "-Wunused-parameter" "-Wunused-value"
    "-Wunused-variable" "-Wvariadic-macros" "-Wvolatile-register-var"
    "-Wwrite-strings"
    # Unused switches:
    # "-Wswitch-default": generated ragel code uses switch without default, 
    #                     we cannot do anything about that
    # "-Wmissing-noreturn": we dont care for gcc specific attributes
    # "-Wpadded": also warns when it's impossible to shrink padding
    # "-Wunsafe-loop-optimizations": emits a warning for each for-range loop
  )
ENDIF(CMAKE_COMPILER_IS_GNUCXX)


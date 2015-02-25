#### html-extract

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)
INCLUDE(ExternalProject) # available since 2.8.7
#SET(CMAKE_VERBOSE_MAKEFILE ON)

PROJECT(html-extract)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()

ADD_DEFINITIONS("-std=c++11")

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")

# Generate ragel state machine
# ADD_CUSTOM_COMMAND is unsuitable, because there is no (non-hackish) way to
# force cmake to run it on every call to make.
# The best way for now is to manually call cmake every time there is a change
# in the parser.
EXECUTE_PROCESS(
  COMMAND
  "${PROJECT_SOURCE_DIR}/scripts/run_ragel.sh"
  "${PROJECT_SOURCE_DIR}/src/hext/parser.h.rl"
  "${PROJECT_SOURCE_DIR}/src/hext/parser.h")
EXECUTE_PROCESS(
  COMMAND
  "${PROJECT_SOURCE_DIR}/scripts/run_ragel.sh"
  "${PROJECT_SOURCE_DIR}/src/hext/parser.cpp.rl"
  "${PROJECT_SOURCE_DIR}/src/hext/parser.cpp")


###### EXTERNAL DEPENDENCIES ##############################
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)

#
### download rapidjson
ExternalProject_Add(
    rapidjson
    GIT_REPOSITORY https://github.com/miloyip/rapidjson.git
    TIMEOUT 10

    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""

    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# use rapidjson's include/ directory as an additional include directory
# (rapidjson is header only)
ExternalProject_Get_Property(rapidjson source_dir)
INCLUDE_DIRECTORIES(SYSTEM ${source_dir}/include)
###########################################################

#
### download and build gumbo
ExternalProject_Add(
    gumbo-parser
    GIT_REPOSITORY https://github.com/google/gumbo-parser.git
    TIMEOUT 10

    CONFIGURE_COMMAND ./autogen.sh COMMAND ./configure --prefix=${CMAKE_BINARY_DIR}
    BUILD_COMMAND make
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""

    BUILD_IN_SOURCE ON
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# use gumbo's include/ directory as an additional include directory
ExternalProject_Get_Property(gumbo-parser source_dir)
INCLUDE_DIRECTORIES(${source_dir}/src)

# add gumbo's library directory when linking
ExternalProject_Get_Property(gumbo-parser binary_dir)
# LINK_DIRECTORIES will apply only to targets created after it is called
LINK_DIRECTORIES(${binary_dir}/.libs)
###########################################################

ADD_EXECUTABLE(
  html-extract
  "${PROJECT_SOURCE_DIR}/src/hext/node-util.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/string-util.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/parser.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/rule.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/rule-builder.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/pattern-builder.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/file.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/match-tree.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/html.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/program-options.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/pattern/attr-test.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/pattern/literal-test.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/pattern/regex-test.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/pattern/match-pattern.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/pattern/attribute-match.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/pattern/builtin-match.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/pattern/capture-pattern.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/pattern/attribute-capture.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/pattern/builtin-capture.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/builtins.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/rule-patterns.cpp"
  "${PROJECT_SOURCE_DIR}/src/main.cpp")
ADD_DEPENDENCIES(html-extract gumbo-parser rapidjson)
TARGET_LINK_LIBRARIES(html-extract gumbo boost_program_options boost_regex)

###### WARNINGS ###########################################
# always show warnings
# clang
IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  ADD_DEFINITIONS("-Weverything")
ENDIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

# g++
IF(CMAKE_COMPILER_IS_GNUCXX)
  ADD_DEFINITIONS(
    "-pedantic" "-pedantic-errors" "-Wall" "-Wcast-align" "-Wcast-qual"
    "-Wchar-subscripts" "-Wcomment" "-Wconversion" "-Wctor-dtor-privacy"
    "-Wdisabled-optimization" "-Weffc++" "-Wextra" "-Wfloat-equal"
    "-Wformat=2" "-Wformat-nonliteral" "-Wformat-security" "-Wformat-y2k"
    "-Wimport" "-Winit-self" "-Winline" "-Winvalid-pch" "-Wlogical-op"
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
###########################################################

###### BUILD OPTIONS ######################################
OPTION(TCMALLOC "Link with libtcmalloc" OFF)
IF(TCMALLOC)
  TARGET_LINK_LIBRARIES(html-extract tcmalloc)

  # -fno-omit-frame-pointer must be set if you configured gperftools with
  # --enable-frame-pointers
  #ADD_DEFINITIONS("-fno-omit-frame-pointer")

  # force gcc to use tcmalloc
  IF(CMAKE_COMPILER_IS_GNUCXX)
    ADD_DEFINITIONS(
      "-fno-builtin-malloc" "-fno-builtin-calloc"
      "-fno-builtin-realloc" "-fno-builtin-free")
  ENDIF(CMAKE_COMPILER_IS_GNUCXX)
ENDIF(TCMALLOC)

# force debug symbols (e.g. cmake -DCMAKE_BUILD_TYPE=Release -DSYMBOLS=ON)
OPTION(SYMBOLS "Add debugging symbols" OFF)
IF(SYMBOLS)
  ADD_DEFINITIONS("-g")
ENDIF(SYMBOLS)

# enable whole-program optimization on gcc
OPTION(WPO  "Use whole-program optimization on gcc" OFF)
IF(WPO)
  IF(CMAKE_COMPILER_IS_GNUCXX)
    ADD_DEFINITIONS("-fwhole-program")
    SET(CMAKE_EXE_LINKER_FLAGS "-fwhole-program")
  ELSE()
    MESSAGE(STATUS "compiler not g++, cannot use -fwhole-program")
  ENDIF()
ENDIF(WPO)

# gprof build
OPTION(GPROF "gprof build" OFF)
IF(GPROF)
  # -pg must be set when compiling and linking
  ADD_DEFINITIONS("-pg")
  SET(CMAKE_EXE_LINKER_FLAGS "-pg")
ENDIF(GPROF)
###########################################################


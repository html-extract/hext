#### html-extract

#SET(CMAKE_VERBOSE_MAKEFILE ON)

PROJECT(html-extract)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules/")
INCLUDE(ExternalProject) # available since 2.8.7
INCLUDE(HextForceCPP11)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF(NOT CMAKE_BUILD_TYPE)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/html-extract")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/libhext/include")

# Generate ragel state machine
# ADD_CUSTOM_COMMAND is unsuitable, because there is no (non-hackish) way to
# force cmake to run it on every call to make.
# The best way for now is to manually call cmake every time there is a change
# in the parser.
EXECUTE_PROCESS(
  COMMAND
  "${PROJECT_SOURCE_DIR}/scripts/run_ragel.sh"
  "${PROJECT_SOURCE_DIR}/libhext/ragel/Parser.h.rl"
  "${PROJECT_SOURCE_DIR}/libhext/include/hext/Parser.h")
EXECUTE_PROCESS(
  COMMAND
  "${PROJECT_SOURCE_DIR}/scripts/run_ragel.sh"
  "${PROJECT_SOURCE_DIR}/libhext/ragel/Parser.cpp.rl"
  "${PROJECT_SOURCE_DIR}/libhext/src/Parser.cpp")


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
  "${PROJECT_SOURCE_DIR}/libhext/src/Builtins.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/Hext.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/Html.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/NodeUtil.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/Parser.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/PatternBuilder.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/pattern/AttributeCapture.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/pattern/AttributeMatch.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/pattern/BuiltinCapture.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/pattern/BuiltinMatch.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/pattern/CapturePattern.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/pattern/LiteralTest.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/pattern/MatchPattern.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/pattern/RegexTest.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/pattern/ValueTest.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/ResultTree.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/RuleBuilder.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/RulePatterns.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/Rule.cpp"
  "${PROJECT_SOURCE_DIR}/libhext/src/StringUtil.cpp"
  "${PROJECT_SOURCE_DIR}/html-extract/htmlext/File.cpp"
  "${PROJECT_SOURCE_DIR}/html-extract/htmlext/Json.cpp"
  "${PROJECT_SOURCE_DIR}/html-extract/htmlext/ProgramOptions.cpp"
  "${PROJECT_SOURCE_DIR}/html-extract/main.cpp")
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
###########################################################

###### BUILD OPTIONS ######################################
# Option TCMALLOC, default OFF
# Link with libtcmalloc, i.e. cmake -DTCMALLOC=ON
SET(HEXT_LINK_TCMALLOC_TARGET html-extract)
INCLUDE(HextOptionLinkTcmalloc)

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


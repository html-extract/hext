#### html-extract

#SET(CMAKE_VERBOSE_MAKEFILE ON)

PROJECT(html-extract)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules/")
INCLUDE(ExternalProject) # available since 2.8.7
# Force flag -std=c++11.
INCLUDE(HextForceCPP11)
# Enable all (reasonable) warnings with Clang and GCC.
INCLUDE(HextEnableWarnings)
# If build type was not specified, build Release.
INCLUDE(HextDefaultBuildRelease)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/html-extract")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/libhext/include")

###### DEPENDENCIES ##############################
FIND_PACKAGE(Boost COMPONENTS regex program_options)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)
INCLUDE(HextExternalProjectRapidJson)

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
TARGET_LINK_LIBRARIES(
  html-extract
  gumbo
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_REGEX_LIBRARY})

###### BUILD OPTIONS ######################################
# Option TCMALLOC, default OFF
# Link with libtcmalloc, i.e. cmake -DTCMALLOC=ON
SET(HEXT_LINK_TCMALLOC_TARGET html-extract)
INCLUDE(HextOptionLinkTcmalloc)

# Option RUNRAGEL, default OFF
# Call run_ragel.sh to generate the parser.
INCLUDE(HextOptionRunRagel)

# Option GPROF, default OFF
# GNU gprof build
INCLUDE(HextOptionGprof)
###########################################################


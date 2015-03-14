###### HTML-EXTRACT ############################################################
PROJECT(html-extract)

# Cmake module ExternalProject is available since 2.8.7.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Force flag -std=c++11.
INCLUDE(HextForceCPP11)

# Enable all (reasonable) warnings with Clang and GCC.
INCLUDE(HextEnableWarnings)

# If build type was not specified, build Release.
INCLUDE(HextDefaultBuildRelease)


###### DEPENDENCIES ############################################################
FIND_PACKAGE(Boost COMPONENTS regex program_options)
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)
INCLUDE(HextExternalProjectRapidJson)
INCLUDE(HextExternalProjectGumbo)


###### INCLUDES ################################################################
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/html-extract")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/libhext/include")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})


###### SOURCES #################################################################
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
ADD_DEPENDENCIES(html-extract gumbo rapidjson)
TARGET_LINK_LIBRARIES(
  html-extract
  gumbo.a
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_REGEX_LIBRARY})


###### BUILD OPTIONS ###########################################################

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


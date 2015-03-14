#### html-extract-test

#SET(CMAKE_VERBOSE_MAKEFILE on)

PROJECT(html-extract-test)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake")
INCLUDE(ExternalProject) # available since 2.8.7
INCLUDE(HextForceCPP11)

# undefine NDEBUG; this way asserts won't be removed in relase mode
ADD_DEFINITIONS(-UNDEBUG)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../libhext/include")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../html-extract")

###### EXTERNAL DEPENDENCIES ##############################
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)
INCLUDE(HextExternalProjectGoogleTest)
INCLUDE(HextExternalProjectRapidJson)
INCLUDE(HextExternalProjectGumbo)


ADD_EXECUTABLE(
  html-extract-test
  "${PROJECT_SOURCE_DIR}/../libhext/src/Builtins.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/Hext.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/Html.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/NodeUtil.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/Parser.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/PatternBuilder.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/pattern/AttributeCapture.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/pattern/AttributeMatch.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/pattern/BuiltinCapture.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/pattern/BuiltinMatch.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/pattern/CapturePattern.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/pattern/LiteralTest.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/pattern/MatchPattern.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/pattern/RegexTest.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/pattern/ValueTest.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/ResultTree.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/RuleBuilder.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/RulePatterns.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/Rule.cpp"
  "${PROJECT_SOURCE_DIR}/../libhext/src/StringUtil.cpp"
  "${PROJECT_SOURCE_DIR}/../html-extract/htmlext/File.cpp"
  "${PROJECT_SOURCE_DIR}/../html-extract/htmlext/Json.cpp"
  "${PROJECT_SOURCE_DIR}/../html-extract/htmlext/ProgramOptions.cpp"
  "${PROJECT_SOURCE_DIR}/src/main.cpp")

ADD_DEPENDENCIES(
  html-extract-test
  gumbo-parser
  rapidjson
  googletest)
TARGET_LINK_LIBRARIES(
  html-extract-test
  gumbo.a
  boost_program_options
  boost_regex
  gtest
  pthread)

###### BUILD OPTIONS ######################################
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
###########################################################


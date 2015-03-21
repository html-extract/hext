###### HTML-EXTRACT-TEST #######################################################
PROJECT(html-extract-test)

# Cmake module ExternalProject is available since 2.8.7.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake")

# Force flag -std=c++11.
INCLUDE(HextForceCPP11)

# Enable all (reasonable) warnings with Clang and GCC.
INCLUDE(HextEnableWarnings)


###### DEPENDENCIES ############################################################
FIND_PACKAGE(Boost COMPONENTS regex program_options)
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)
INCLUDE(HextExternalProjectGoogleTest)
INCLUDE(HextExternalProjectRapidJson)
INCLUDE(HextExternalProjectGumbo)


###### INCLUDES ################################################################
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../libhext/include")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../html-extract")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})


###### SOURCES #################################################################
SET(LIBHEXT_SRC "${PROJECT_SOURCE_DIR}/../libhext/src")
SET(HTMLEXT_SRC "${PROJECT_SOURCE_DIR}/../html-extract/htmlext")
ADD_EXECUTABLE(
  html-extract-test
  "${LIBHEXT_SRC}/Builtins.cpp"
  "${LIBHEXT_SRC}/Hext.cpp"
  "${LIBHEXT_SRC}/Html.cpp"
  "${LIBHEXT_SRC}/NodeUtil.cpp"
  "${LIBHEXT_SRC}/Parser.cpp"
  "${LIBHEXT_SRC}/PatternBuilder.cpp"
  "${LIBHEXT_SRC}/pattern/AttributeCapture.cpp"
  "${LIBHEXT_SRC}/pattern/AttributeMatch.cpp"
  "${LIBHEXT_SRC}/pattern/BuiltinCapture.cpp"
  "${LIBHEXT_SRC}/pattern/BuiltinMatch.cpp"
  "${LIBHEXT_SRC}/pattern/CapturePattern.cpp"
  "${LIBHEXT_SRC}/pattern/LiteralTest.cpp"
  "${LIBHEXT_SRC}/pattern/MatchPattern.cpp"
  "${LIBHEXT_SRC}/pattern/RegexTest.cpp"
  "${LIBHEXT_SRC}/pattern/ValueTest.cpp"
  "${LIBHEXT_SRC}/ResultTree.cpp"
  "${LIBHEXT_SRC}/RuleBuilder.cpp"
  "${LIBHEXT_SRC}/RulePatterns.cpp"
  "${LIBHEXT_SRC}/Rule.cpp"
  "${LIBHEXT_SRC}/StringUtil.cpp"
  "${HTMLEXT_SRC}/File.cpp"
  "${HTMLEXT_SRC}/Json.cpp"
  "${HTMLEXT_SRC}/ProgramOptions.cpp"
  "${PROJECT_SOURCE_DIR}/src/main.cpp")
ADD_DEPENDENCIES(html-extract-test gumbo rapidjson googletest)
TARGET_LINK_LIBRARIES(
  html-extract-test
  gumbo.a
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_REGEX_LIBRARY}
  gtest
  pthread)


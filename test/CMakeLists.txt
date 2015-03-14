#### html-extract-test

#SET(CMAKE_VERBOSE_MAKEFILE on)

PROJECT(html-extract-test)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/../cmake")
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
  gumbo
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


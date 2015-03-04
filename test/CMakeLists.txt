#### html-extract-test

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)
INCLUDE(ExternalProject) # available since 2.8.7
#SET(CMAKE_VERBOSE_MAKEFILE on)

PROJECT(html-extract-test)

ADD_DEFINITIONS("-std=c++11")
# undefine NDEBUG; this way asserts won't be removed in relase mode
ADD_DEFINITIONS(-UNDEBUG)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")
# add html-extract's src/ directory as an additional include directory
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../src")


###### EXTERNAL DEPENDENCIES ##############################
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)

#
### download and build googletest
ExternalProject_Add(
    googletest
    URL http://googletest.googlecode.com/files/gtest-1.7.0.zip
    TIMEOUT 10

    UPDATE_COMMAND ""
    INSTALL_COMMAND ""

    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# use googletest's include/ directory as an additional include directory
ExternalProject_Get_Property(googletest source_dir)
INCLUDE_DIRECTORIES(${source_dir}/include)

# add googletest's library directory when linking
ExternalProject_Get_Property(googletest binary_dir)
# LINK_DIRECTORIES will apply only to targets created after it is called
LINK_DIRECTORIES(${binary_dir})
###########################################################

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
  "${PROJECT_SOURCE_DIR}/../src/hext/node-util.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/string-util.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/parser.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/rule.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/rule-builder.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/pattern-builder.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/file.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/result-tree.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/html.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/program-options.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/pattern/value-test.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/pattern/literal-test.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/pattern/regex-test.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/pattern/match-pattern.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/pattern/attribute-match.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/pattern/builtin-match.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/pattern/capture-pattern.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/pattern/attribute-capture.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/pattern/builtin-capture.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/builtins.cpp"
  "${PROJECT_SOURCE_DIR}/../src/hext/rule-patterns.cpp"
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


###### LIBHEXT #################################################################
PROJECT(libhext)

# Cmake module ExternalProject is available since 2.8.7.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)

SET(LIBHEXT_LOADED "true")

SET(
  CMAKE_MODULE_PATH
  ${PROJECT_SOURCE_DIR}/../cmake
  ${PROJECT_SOURCE_DIR}/../cmake/thirdparty)

# Force flag -std=c++11.
INCLUDE(HextForceCPP11)

# Enable all (reasonable) warnings with Clang and GCC.
INCLUDE(HextEnableWarnings)

# If build type was not specified, build Release.
INCLUDE(HextDefaultBuildRelease)


###### VERSION #################################################################
SET(PROJECT_VERSION_MAJOR 0)
SET(PROJECT_VERSION_MINOR 1)
SET(PROJECT_VERSION_PATCH 0)
SET(
  HEXT_VERSION_FILE_SOURCE
  "${PROJECT_SOURCE_DIR}/src/Version.cpp.in")
INCLUDE(HextGenerateVersionFile)


###### DEPENDENCIES ############################################################
FIND_PACKAGE(Boost COMPONENTS regex)
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)
FIND_PACKAGE(Gumbo)
IF(NOT LIBGUMBO_FOUND)
  INCLUDE(HextExternalProjectGumbo)
ENDIF(NOT LIBGUMBO_FOUND)


###### INCLUDES ################################################################
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
IF(LIBGUMBO_FOUND)
  INCLUDE_DIRECTORIES(${GUMBO_INCLUDE_DIR})
ENDIF(LIBGUMBO_FOUND)


###### SOURCES #################################################################
ADD_LIBRARY(
  hext SHARED
  "${PROJECT_SOURCE_DIR}/src/BeginsWithTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/ContainsTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/ContainsWordsTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/EndsWithTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/EqualsTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/Hext.cpp"
  "${PROJECT_SOURCE_DIR}/src/Html.cpp"
  "${PROJECT_SOURCE_DIR}/src/MatchContext.cpp"
  "${PROJECT_SOURCE_DIR}/src/NegateTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/NodeUtil.cpp"
  "${PROJECT_SOURCE_DIR}/src/Parser.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/AttributeCapture.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/AttributeCountMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/AttributeMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/BuiltinCapture.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/BuiltinMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/ChildCountMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/NegateMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/NthChildMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/OnlyChildMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/TextNodeMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/PatternValues.cpp"
  "${PROJECT_SOURCE_DIR}/src/RegexTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/ResultTree.cpp"
  "${PROJECT_SOURCE_DIR}/src/Rule.cpp"
  "${PROJECT_SOURCE_DIR}/src/RuleBuilder.cpp"
  "${PROJECT_SOURCE_DIR}/src/StringUtil.cpp"
  "${PROJECT_SOURCE_DIR}/src/SyntaxError.cpp"
  "${PROJECT_SOURCE_DIR}/src/Version.cpp")
ADD_DEPENDENCIES(hext gumbo-parser)
TARGET_LINK_LIBRARIES(
  hext
  gumbo
  ${Boost_REGEX_LIBRARY})


###### INSTALL #################################################################
INSTALL(TARGETS hext DESTINATION lib)
INSTALL(DIRECTORY include/hext DESTINATION include)


###### EXAMPLE #################################################################
IF(NOT LIBHEXT_NO_EXAMPLE)
  ADD_EXECUTABLE(
    chaining-rules
    "${PROJECT_SOURCE_DIR}/examples/chaining.cpp")
  ADD_DEPENDENCIES(chaining-rules hext)
  TARGET_LINK_LIBRARIES(
    chaining-rules
    hext)
  SET_TARGET_PROPERTIES(
    chaining-rules
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")
  ADD_EXECUTABLE(
    extract-href
    "${PROJECT_SOURCE_DIR}/examples/extract-href.cpp")
  ADD_DEPENDENCIES(extract-href hext)
  TARGET_LINK_LIBRARIES(
    extract-href
    PocoFoundation
    hext)
  SET_TARGET_PROPERTIES(
    extract-href
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")
ENDIF(NOT LIBHEXT_NO_EXAMPLE)


###### TEST ####################################################################
IF(NOT LIBHEXT_NO_TESTING)
  ENABLE_TESTING()
  IF(NOT LIBHEXT_TEST_LOADED)
    ADD_SUBDIRECTORY("test/")
  ENDIF(NOT LIBHEXT_TEST_LOADED)
ENDIF(NOT LIBHEXT_NO_TESTING)


###### BUILD OPTIONS ###########################################################
# Option RUNRAGEL, default OFF
# Call run_ragel.sh to generate the parser.
INCLUDE(HextOptionRunRagel)



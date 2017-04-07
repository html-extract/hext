###### LIBHEXT #################################################################
# Enable PROJECT() with VERSION parameter.
CMAKE_POLICY(SET CMP0048 NEW)
PROJECT(Hext VERSION 0.6.0)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)

# Force flag -std=c++14.
INCLUDE(HextForceCPP14)

# Enable all (reasonable) warnings with Clang and GCC.
INCLUDE(HextEnableWarnings)

# If build type was not specified, build Release.
INCLUDE(HextDefaultBuildRelease)

# Defines HEXT_COMPILER_IS_CLANG_OR_GCC.
INCLUDE(HextCompilerIsClangOrGcc)


###### VERSION #################################################################
SET(
  HEXT_VERSION_FILE_SOURCE
  "${PROJECT_SOURCE_DIR}/src/Version.cpp.in")
INCLUDE(HextGenerateVersionFile)


###### DEPENDENCIES ############################################################
FIND_PACKAGE(Boost REQUIRED COMPONENTS regex)
FIND_PACKAGE(Gumbo REQUIRED)
FIND_PACKAGE(PocoFoundation QUIET) # optional, see "examples" section
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)


###### LIBHEXT #################################################################
ADD_LIBRARY(
  hext
  "${PROJECT_SOURCE_DIR}/src/AppendPipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/AttributeCapture.cpp"
  "${PROJECT_SOURCE_DIR}/src/AttributeCountMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/AttributeMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/BeginsWithTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/Builtins.cpp"
  "${PROJECT_SOURCE_DIR}/src/CasePipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/ChildCountMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/CollapseWsPipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/ContainsTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/ContainsWordsTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/EndsWithTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/EqualsTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/FunctionCapture.cpp"
  "${PROJECT_SOURCE_DIR}/src/FunctionMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/FunctionValueMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/Html.cpp"
  "${PROJECT_SOURCE_DIR}/src/NegateMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/NegateTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/NodeUtil.cpp"
  "${PROJECT_SOURCE_DIR}/src/NthChildMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/OnlyChildMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/ParseHext.cpp"
  "${PROJECT_SOURCE_DIR}/src/Parser.cpp"
  "${PROJECT_SOURCE_DIR}/src/PatternValues.cpp"
  "${PROJECT_SOURCE_DIR}/src/PrependPipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/RegexPipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/RegexReplacePipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/RegexTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/Rule.cpp"
  "${PROJECT_SOURCE_DIR}/src/RuleMatching.cpp"
  "${PROJECT_SOURCE_DIR}/src/StringPipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/StringUtil.cpp"
  "${PROJECT_SOURCE_DIR}/src/SyntaxError.cpp"
  "${PROJECT_SOURCE_DIR}/src/TrimPipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/Version.cpp")
TARGET_LINK_LIBRARIES(
  hext
  ${Gumbo_LIBRARY}
  ${Boost_REGEX_LIBRARY})
SET_TARGET_PROPERTIES(
  hext PROPERTIES
  VERSION "${Hext_VERSION}"
  SOVERSION "${Hext_VERSION_MAJOR}.${Hext_VERSION_MINOR}")
IF(HEXT_COMPILER_IS_CLANG_OR_GCC)
  SET_TARGET_PROPERTIES(hext PROPERTIES CXX_VISIBILITY_PRESET hidden)
ENDIF(HEXT_COMPILER_IS_CLANG_OR_GCC)


###### INCLUDES ################################################################
TARGET_INCLUDE_DIRECTORIES(hext PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>")
TARGET_INCLUDE_DIRECTORIES(hext PUBLIC ${Boost_INCLUDE_DIRS})
TARGET_INCLUDE_DIRECTORIES(hext PUBLIC ${Gumbo_INCLUDE_DIR})


###### CMAKE PACKAGE ###########################################################
SET(HEXT_PACKAGE_VERSION_FILE
    "${CMAKE_CURRENT_BINARY_DIR}/HextConfigVersion.cmake")
SET(HEXT_PACKAGE_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/HextConfig.cmake")
SET(HEXT_PACKAGE_INSTALL_DIR "lib/cmake/hext")
SET(INCLUDE_INSTALL_DIR "include")

INCLUDE(CMakePackageConfigHelpers)
WRITE_BASIC_PACKAGE_VERSION_FILE(
  "${HEXT_PACKAGE_VERSION_FILE}" COMPATIBILITY SameMajorVersion)
CONFIGURE_PACKAGE_CONFIG_FILE(
  "${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in"
  "${HEXT_PACKAGE_CONFIG_FILE}"
  INSTALL_DESTINATION "${HEXT_PACKAGE_INSTALL_DIR}"
  PATH_VARS INCLUDE_INSTALL_DIR)


###### INSTALL #################################################################
INSTALL(TARGETS hext
        EXPORT "HextTargets"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib"
        INCLUDES DESTINATION ${INCLUDE_INSTALL_DIR})
INSTALL(DIRECTORY "${PROJECT_SOURCE_DIR}/include/hext"
        DESTINATION ${INCLUDE_INSTALL_DIR})
INSTALL(FILES       "${HEXT_PACKAGE_CONFIG_FILE}" "${HEXT_PACKAGE_VERSION_FILE}"
        DESTINATION "${HEXT_PACKAGE_INSTALL_DIR}")
INSTALL(EXPORT "HextTargets"
        DESTINATION "${HEXT_PACKAGE_INSTALL_DIR}")


###### EXAMPLES ################################################################
ADD_EXECUTABLE(
  mixed
  "${PROJECT_SOURCE_DIR}/examples/mixed.cpp")
ADD_DEPENDENCIES(mixed hext)
TARGET_LINK_LIBRARIES(
  mixed
  hext)
SET_TARGET_PROPERTIES(
  mixed
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")
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
IF(${POCOFOUNDATION_FOUND})
  INCLUDE_DIRECTORIES(${PocoFoundation_INCLUDE_DIR})
  ADD_EXECUTABLE(
    extract-href
    "${PROJECT_SOURCE_DIR}/examples/extract-href.cpp")
  ADD_DEPENDENCIES(extract-href hext)
  TARGET_LINK_LIBRARIES(
    extract-href
    ${PocoFoundation_LIBRARY}
    hext)
  SET_TARGET_PROPERTIES(
    extract-href
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")
ENDIF(${POCOFOUNDATION_FOUND})


###### BUILD OPTIONS ###########################################################
# Option RUNRAGEL, default OFF
# Calls run-ragel.sh to generate the parser.
INCLUDE(HextOptionRunRagel)

# Option SANITIZEADDRESS, default OFF
# Adds -fsanitize=address and -fno-omit-frame-pointer to compiler flags
INCLUDE(HextOptionSanitizeAddress)

# Option SANITIZEUNDEFINED, default OFF
# Adds -fsanitize=undefined and -fno-omit-frame-pointer to compiler flags
INCLUDE(HextOptionSanitizeUndefined)


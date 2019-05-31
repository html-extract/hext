###### LIBHEXT #################################################################

# Allow cmake to set VERSION variables
# https://cmake.org/cmake/help/latest/policy/CMP0048.html
cmake_policy(SET CMP0048 NEW)

project(Hext VERSION 0.7.2)

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Add the top-level cmake module directory to CMAKE_MODULE_PATH
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/../cmake)

include(HextEnableWarnings)

# If build type was not specified, build Release.
include(HextDefaultBuildRelease)

# Defines HEXT_COMPILER_IS_CLANG_OR_GCC.
include(HextCompilerIsClangOrGcc)


###### VERSION #################################################################
configure_file(
  "${PROJECT_SOURCE_DIR}/src/Version.cpp.in"
  "${PROJECT_SOURCE_DIR}/src/Version.cpp"
  # Restrict variable replacement to references of the form @VAR@
  @ONLY)


###### DEPENDENCIES ############################################################
find_package(Boost REQUIRED COMPONENTS regex)
find_package(Gumbo REQUIRED)


###### LIBHEXT #################################################################
add_library(
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
target_compile_features(hext PUBLIC cxx_std_17)
hext_enable_warnings(hext PRIVATE)
target_link_libraries(
  hext
  ${Gumbo_LIBRARY}
  ${Boost_REGEX_LIBRARY})
set_target_properties(
  hext PROPERTIES
  VERSION "${Hext_VERSION}"
  SOVERSION "${Hext_VERSION_MAJOR}.${Hext_VERSION_MINOR}")
if(HEXT_COMPILER_IS_CLANG_OR_GCC)
  set_target_properties(hext PROPERTIES CXX_VISIBILITY_PRESET hidden)
endif()


###### INCLUDES ################################################################
target_include_directories(hext PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>")
target_include_directories(hext PUBLIC ${Boost_INCLUDE_DIRS})
target_include_directories(hext PUBLIC ${Gumbo_INCLUDE_DIR})


###### CMAKE PACKAGE ###########################################################
set(HEXT_PACKAGE_VERSION_FILE
    "${CMAKE_CURRENT_BINARY_DIR}/HextConfigVersion.cmake")
set(HEXT_PACKAGE_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/HextConfig.cmake")
set(HEXT_PACKAGE_INSTALL_DIR "lib/cmake/hext")
set(INCLUDE_INSTALL_DIR "include")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${HEXT_PACKAGE_VERSION_FILE}" COMPATIBILITY SameMajorVersion)
configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in"
  "${HEXT_PACKAGE_CONFIG_FILE}"
  INSTALL_DESTINATION "${HEXT_PACKAGE_INSTALL_DIR}"
  PATH_VARS INCLUDE_INSTALL_DIR)


###### INSTALL #################################################################
install(TARGETS hext
        EXPORT "HextTargets"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib"
        INCLUDES DESTINATION ${INCLUDE_INSTALL_DIR})
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/hext"
        DESTINATION ${INCLUDE_INSTALL_DIR})
install(FILES       "${HEXT_PACKAGE_CONFIG_FILE}" "${HEXT_PACKAGE_VERSION_FILE}"
        DESTINATION "${HEXT_PACKAGE_INSTALL_DIR}")
install(EXPORT "HextTargets"
        DESTINATION "${HEXT_PACKAGE_INSTALL_DIR}")


###### EXAMPLES ################################################################
option(BUILD_EXAMPLES "Build libhext usage examples" OFF)
if(BUILD_EXAMPLES)
  find_package(PocoFoundation QUIET)
  add_executable(
    mixed
    "${PROJECT_SOURCE_DIR}/examples/mixed.cpp")
  add_dependencies(mixed hext)
  target_link_libraries(
    mixed
    hext)
  set_target_properties(
    mixed
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")
  add_executable(
    chaining-rules
    "${PROJECT_SOURCE_DIR}/examples/chaining.cpp")
  add_dependencies(chaining-rules hext)
  target_link_libraries(
    chaining-rules
    hext)
  set_target_properties(
    chaining-rules
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")
  if(${POCOFOUNDATION_FOUND})
    include_directories(${PocoFoundation_INCLUDE_DIR})
    add_executable(
      extract-href
      "${PROJECT_SOURCE_DIR}/examples/extract-href.cpp")
    add_dependencies(extract-href hext)
    target_link_libraries(
      extract-href
      ${PocoFoundation_LIBRARY}
      hext)
    set_target_properties(
      extract-href
      PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")
  endif()
endif()


###### BUILD OPTIONS ###########################################################
# Option RUNRAGEL, default OFF
# Calls run-ragel.sh to generate the parser.
include(HextOptionRunRagel)

# Option SANITIZEUNDEFINED, default OFF
# Adds -fsanitize=undefined and -fno-omit-frame-pointer to compiler flags
include(HextOptionSanitizeUndefined)


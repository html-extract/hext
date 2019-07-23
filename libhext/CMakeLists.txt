###### LIBHEXT #################################################################

# Allow cmake to set VERSION variables
# https://cmake.org/cmake/help/latest/policy/CMP0048.html
cmake_policy(SET CMP0048 NEW)

project(Hext VERSION 0.8.2)

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
  "Version.cpp"
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
  "${CMAKE_CURRENT_BINARY_DIR}/Version.cpp")
add_library(hext::hext ALIAS hext)
target_compile_features(hext PUBLIC cxx_std_17)
hext_enable_warnings(hext PRIVATE)
target_link_libraries(hext
  PUBLIC
    Gumbo::Gumbo
    Boost::regex)
set_target_properties(
  hext PROPERTIES
  VERSION "${Hext_VERSION}"
  SOVERSION "${Hext_VERSION_MAJOR}.${Hext_VERSION_MINOR}")
if(HEXT_COMPILER_IS_CLANG_OR_GCC)
  set_target_properties(hext PROPERTIES CXX_VISIBILITY_PRESET hidden)
endif()
target_include_directories(hext
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)


###### CMAKE PACKAGE ###########################################################
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/HextConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion)


###### INSTALL #################################################################
include(GNUInstallDirs)
install(TARGETS hext
        EXPORT HextTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/hext"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES "${PROJECT_SOURCE_DIR}/cmake/HextConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/HextConfigVersion.cmake"
        DESTINATION lib/cmake/hext)
install(EXPORT HextTargets
        FILE HextTargets.cmake
        NAMESPACE hext::
        DESTINATION lib/cmake/hext)


###### BUILD OPTIONS ###########################################################
# Option RUNRAGEL, default OFF
# Calls run-ragel.sh to generate the parser.
include(HextOptionRunRagel)


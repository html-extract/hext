###### HTMLEXT #################################################################
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

# https://cmake.org/cmake/help/latest/policy/CMP0167.html
# Prefer Boost-installed cmake configuration for package Boost.
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

project(htmlext VERSION 1.0.13)

# Add the top-level cmake module directory to CMAKE_MODULE_PATH
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)

include(HextEnableWarnings)

# If build type was not specified, build Release.
include(HextDefaultBuildRelease)


###### VERSION #################################################################
configure_file(
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/Version.cpp.in"
  "Version.cpp"
  # Restrict variable replacement to references of the form @VAR@
  @ONLY)


###### DEPENDENCIES ############################################################
add_subdirectory("libhext")
find_package(Boost COMPONENTS program_options REQUIRED)
find_package(RapidJSON REQUIRED)


###### SOURCES #################################################################
add_executable(
  htmlext
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/ErrorOutput.cpp"
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/File.cpp"
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/Json.cpp"
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/ProgramOptions.cpp"
  "${CMAKE_CURRENT_BINARY_DIR}/Version.cpp"
  "${PROJECT_SOURCE_DIR}/htmlext/main.cpp")
hext_enable_warnings(htmlext PRIVATE)
target_include_directories(htmlext
  PRIVATE
    "${PROJECT_SOURCE_DIR}/htmlext")
target_link_libraries(htmlext
    hext::hext
    RapidJSON::RapidJSON
    Boost::program_options)


###### INSTALL #################################################################
include(GNUInstallDirs)
install(TARGETS htmlext RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/man/htmlext.1
        DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)


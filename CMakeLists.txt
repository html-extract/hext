###### HTMLEXT #################################################################

# Allow cmake to set VERSION variables
# https://cmake.org/cmake/help/latest/policy/CMP0048.html
cmake_policy(SET CMP0048 NEW)
project(htmlext VERSION 0.6)

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

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


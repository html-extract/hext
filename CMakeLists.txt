###### HTMLEXT #################################################################

# Allow cmake to set VERSION variables
# https://cmake.org/cmake/help/latest/policy/CMP0048.html
cmake_policy(SET CMP0048 NEW)
project(htmlext VERSION 0.5)

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(HextEnableWarnings)

# If build type was not specified, build Release.
include(HextDefaultBuildRelease)


###### VERSION #################################################################
set(
  HEXT_VERSION_FILE_SOURCE
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/Version.cpp.in")
include(HextGenerateVersionFile)


###### DEPENDENCIES ############################################################
include_directories("${PROJECT_SOURCE_DIR}/htmlext")

if(USE_SYSTEM_LIBHEXT)
  find_package(Hext REQUIRED)
  include_directories(${HEXT_INCLUDE_DIR})
else()
  add_subdirectory("libhext")
  include_directories("${PROJECT_SOURCE_DIR}/libhext/include")
endif()

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# If RapidJSON is not found in system, download it. RapidJSON is a header only
# library.
find_package(RapidJSON QUIET)
if(NOT RapidJSON_INCLUDE_DIRS)
  message("Will download rapidjson automatically")
  include(HextExternalProjectRapidJson)
else()
  include_directories(${RapidJSON_INCLUDE_DIRS})
endif()
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)


###### SOURCES #################################################################
add_executable(
  htmlext
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/ErrorOutput.cpp"
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/File.cpp"
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/Json.cpp"
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/ProgramOptions.cpp"
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/Version.cpp"
  "${PROJECT_SOURCE_DIR}/htmlext/main.cpp")
hext_enable_warnings(htmlext PRIVATE)
if(USE_SYSTEM_LIBHEXT)
  set(TARGET_LINK_LIBHEXT ${HEXT_LIBRARY})
else()
  add_dependencies(htmlext hext)
  set(TARGET_LINK_LIBHEXT hext)
endif()
# If RapidJSON wasn't found via FIND_PACKAGE it will be downloaded via
# ExternalProject_Add.
if(NOT RapidJSON_INCLUDE_DIRS)
  add_dependencies(htmlext rapidjson)
endif()
target_link_libraries(
  htmlext
  ${TARGET_LINK_LIBHEXT}
  ${Boost_PROGRAM_OPTIONS_LIBRARY})


###### INSTALL #################################################################
install(TARGETS htmlext DESTINATION bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/man/htmlext.1 DESTINATION man/man1)


###### BUILD OPTIONS ###########################################################
# Option TCMALLOC, default OFF
# Link with libtcmalloc, i.e. cmake -DTCMALLOC=ON
set(HEXT_LINK_TCMALLOC_TARGET htmlext)
include(HextOptionLinkTcmalloc)

# Option GPROF, default OFF
# GNU gprof build
include(HextOptionGprof)

# Option SANITIZEADDRESS, default OFF
# Adds -fsanitize=address and -fno-omit-frame-pointer to compiler flags
include(HextOptionSanitizeAddress)

# Option SANITIZEUNDEFINED, default OFF
# Adds -fsanitize=undefined and -fno-omit-frame-pointer to compiler flags
include(HextOptionSanitizeUndefined)


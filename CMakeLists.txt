###### HTMLEXT #################################################################
# Enable PROJECT() with VERSION parameter.
CMAKE_POLICY(SET CMP0048 NEW)
PROJECT(htmlext VERSION 0.2)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Force flag -std=c++14.
INCLUDE(HextForceCPP14)

# Enable all (reasonable) warnings with Clang and GCC.
INCLUDE(HextEnableWarnings)

# If build type was not specified, build Release.
INCLUDE(HextDefaultBuildRelease)


###### VERSION #################################################################
SET(
  HEXT_VERSION_FILE_SOURCE
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/Version.cpp.in")
INCLUDE(HextGenerateVersionFile)


###### DEPENDENCIES ############################################################
ADD_SUBDIRECTORY("libhext")
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
# If RapidJSON is not found in system, download it. RapidJSON is a header only
# library.
FIND_PACKAGE(RapidJSON QUIET)
IF(NOT RAPIDJSON_INCLUDE_DIRS)
  MESSAGE("Will download rapidjson automatically")
  INCLUDE(HextExternalProjectRapidJson)
ELSE(NOT RAPIDJSON_INCLUDE_DIRS)
  INCLUDE_DIRECTORIES(${RAPIDJSON_INCLUDE_DIRS})
ENDIF(NOT RAPIDJSON_INCLUDE_DIRS)
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)


###### INCLUDES ################################################################
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/htmlext")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/libhext/include")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})


###### SOURCES #################################################################
ADD_EXECUTABLE(
  htmlext
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/ErrorOutput.cpp"
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/File.cpp"
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/Json.cpp"
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/ProgramOptions.cpp"
  "${PROJECT_SOURCE_DIR}/htmlext/htmlext/Version.cpp"
  "${PROJECT_SOURCE_DIR}/htmlext/main.cpp")
ADD_DEPENDENCIES(htmlext hext)
# If RapidJSON wasn't found via FIND_PACKAGE it will be downloaded via
# ExternalProject_Add.
IF(NOT RAPIDJSON_INCLUDE_DIRS)
  ADD_DEPENDENCIES(htmlext rapidjson)
ENDIF(NOT RAPIDJSON_INCLUDE_DIRS)
TARGET_LINK_LIBRARIES(
  htmlext
  hext
  ${Boost_PROGRAM_OPTIONS_LIBRARY})


###### INSTALL #################################################################
INSTALL(TARGETS htmlext DESTINATION bin)


###### BUILD OPTIONS ###########################################################
# Option TCMALLOC, default OFF
# Link with libtcmalloc, i.e. cmake -DTCMALLOC=ON
SET(HEXT_LINK_TCMALLOC_TARGET htmlext)
INCLUDE(HextOptionLinkTcmalloc)

# Option GPROF, default OFF
# GNU gprof build
INCLUDE(HextOptionGprof)

# Option SANITIZEADDRESS, default OFF
# Adds -fsanitize=address and -fno-omit-frame-pointer to compiler flags
INCLUDE(HextOptionSanitizeAddress)

# Option SANITIZEUNDEFINED, default OFF
# Adds -fsanitize=undefined and -fno-omit-frame-pointer to compiler flags
INCLUDE(HextOptionSanitizeUndefined)


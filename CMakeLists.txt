###### HTML-EXTRACT ############################################################
PROJECT(html-extract)

# Cmake module ExternalProject is available since 2.8.7.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Force flag -std=c++11.
INCLUDE(HextForceCPP11)

# Enable all (reasonable) warnings with Clang and GCC.
INCLUDE(HextEnableWarnings)

# If build type was not specified, build Release.
INCLUDE(HextDefaultBuildRelease)


###### DEPENDENCIES ############################################################
ADD_SUBDIRECTORY("libhext")
FIND_PACKAGE(Boost COMPONENTS program_options)
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)
INCLUDE(HextExternalProjectRapidJson)


###### INCLUDES ################################################################
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/html-extract")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/libhext/include")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})


###### SOURCES #################################################################
ADD_EXECUTABLE(
  html-extract
  "${PROJECT_SOURCE_DIR}/html-extract/htmlext/File.cpp"
  "${PROJECT_SOURCE_DIR}/html-extract/htmlext/Json.cpp"
  "${PROJECT_SOURCE_DIR}/html-extract/htmlext/ProgramOptions.cpp"
  "${PROJECT_SOURCE_DIR}/html-extract/main.cpp")
ADD_DEPENDENCIES(html-extract rapidjson hext)
TARGET_LINK_LIBRARIES(
  html-extract
  hext
  ${Boost_PROGRAM_OPTIONS_LIBRARY})


###### BUILD OPTIONS ###########################################################

# Option TCMALLOC, default OFF
# Link with libtcmalloc, i.e. cmake -DTCMALLOC=ON
SET(HEXT_LINK_TCMALLOC_TARGET html-extract)
INCLUDE(HextOptionLinkTcmalloc)

# Option GPROF, default OFF
# GNU gprof build
INCLUDE(HextOptionGprof)


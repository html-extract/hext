###### HEXTJS ##################################################################
PROJECT(hextjs)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../../cmake")

# Force flag -std=c++14.
INCLUDE(HextForceCPP14)

# If build type was not specified, build Release.
INCLUDE(HextDefaultBuildRelease)


###### DEPENDENCIES ############################################################

### LIBHEXT
FIND_PACKAGE(Hext REQUIRED)
INCLUDE_DIRECTORIES(${HEXT_INCLUDE_DIR})

### WRAPPERS
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")


###### NODEJS ##################################################################
ADD_LIBRARY(
  ${PROJECT_NAME} SHARED
  "${PROJECT_SOURCE_DIR}/src/Html.cpp"
  "${PROJECT_SOURCE_DIR}/src/Rule.cpp"
  "${PROJECT_SOURCE_DIR}/src/Hextjs.cpp")
SET_TARGET_PROPERTIES(
  ${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node" OUTPUT_NAME "hext")
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${CMAKE_JS_LIB} ${HEXT_LIBRARY})


###### HEXTJS ##################################################################
project(hextjs)

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Add the top-level cmake module directory to CMAKE_MODULE_PATH
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/../../../cmake)

# Set required C++ standard or abort.
include(HextForceCppStd)

# If build type was not specified, build Release.
include(HextDefaultBuildRelease)


###### DEPENDENCIES ############################################################

### LIBHEXT
find_package(Hext REQUIRED)
include_directories(${HEXT_INCLUDE_DIR})

### WRAPPERS
include_directories("${PROJECT_SOURCE_DIR}/src")


###### NODEJS ##################################################################
add_library(
  ${PROJECT_NAME} SHARED
  "${PROJECT_SOURCE_DIR}/src/Html.cpp"
  "${PROJECT_SOURCE_DIR}/src/Rule.cpp"
  "${PROJECT_SOURCE_DIR}/src/Hextjs.cpp")
set_target_properties(
  ${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node" OUTPUT_NAME "hext")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} ${HEXT_LIBRARY})


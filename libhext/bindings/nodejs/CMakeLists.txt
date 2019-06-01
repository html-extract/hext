###### HEXTJS ##################################################################
project(hextjs)

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Add the top-level cmake module directory to CMAKE_MODULE_PATH
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/../../../cmake)

# If build type was not specified, build Release.
include(HextDefaultBuildRelease)

find_package(Hext REQUIRED)

add_library(
  ${PROJECT_NAME} SHARED
  "${PROJECT_SOURCE_DIR}/src/Html.cpp"
  "${PROJECT_SOURCE_DIR}/src/Rule.cpp"
  "${PROJECT_SOURCE_DIR}/src/Hextjs.cpp")

set_target_properties(
  ${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node" OUTPUT_NAME "hext")

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_JS_INC}
    ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} hext::hext)


###### HEXT-PYTHON #############################################################
PROJECT(hext-python)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../../cmake")

# Force flag -std=c++14.
INCLUDE(HextForceCPP14)

# If build type was not specified, build Release.
INCLUDE(HextDefaultBuildRelease)


###### DEPENDENCIES ############################################################

### SWIG
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

### PYTHON
FIND_PACKAGE(PythonLibs REQUIRED)

### LIBHEXT
FIND_PACKAGE(Hext REQUIRED)
INCLUDE_DIRECTORIES(${HEXT_INCLUDE_DIR})

### WRAPPERS
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../wrapper")


###### SWIG ####################################################################
SET(CMAKE_SWIG_FLAGS "-c++")


###### PYTHON ##################################################################
INCLUDE_DIRECTORIES(SYSTEM ${PYTHON_INCLUDE_PATH})

SET_SOURCE_FILES_PROPERTIES(
  "${PROJECT_SOURCE_DIR}/../hext.i" PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(
  hext python
  "${PROJECT_SOURCE_DIR}/../hext.i"
  "${PROJECT_SOURCE_DIR}/../wrapper/swig-html.cpp"
  "${PROJECT_SOURCE_DIR}/../wrapper/swig-rule.cpp")
SWIG_LINK_LIBRARIES(hext ${HEXT_LIBRARY} ${PYTHON_LIBRARIES})


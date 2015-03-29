###### SWIG-HEXT ###############################################################
PROJECT(swig-hext)

# Cmake module ExternalProject is available since 2.8.7.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake")

# Force flag -std=c++11.
INCLUDE(HextForceCPP11)

# If build type was not specified, build Release.
INCLUDE(HextDefaultBuildRelease)


###### DEPENDENCIES ############################################################

### SWIG
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

### PYTHON
FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(SYSTEM ${PYTHON_INCLUDE_PATH})

### LIBHEXT
# Tell libhext that swig-hext is already loaded
SET(SWIG_HEXT_LOADED "true")
# Avoid circular dependeny by only loading libhext if it wasn't included already
IF(NOT LIBHEXT_LOADED)
  SET(LIBHEXT_NO_TESTING "true")
  ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/.." "libhext")
ENDIF(NOT LIBHEXT_LOADED)
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../../libhext/include")


###### SWIG ####################################################################
SET(CMAKE_SWIG_FLAGS "")
SET(CMAKE_SWIG_OUTDIR ${CMAKE_BINARY_DIR}/swig-hext)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/swig-hext)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/swig-hext)

SET_SOURCE_FILES_PROPERTIES(hext.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(pyhext python hext.i)
SWIG_LINK_LIBRARIES(pyhext hext ${PYTHON_LIBRARIES})


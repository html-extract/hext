###### SWIG-HEXT ###############################################################
PROJECT(swig-hext)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake")

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

### WRAPPERS
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}")


###### SWIG ####################################################################
SET(CMAKE_SWIG_FLAGS "-c++")


###### PYTHON ##################################################################
INCLUDE_DIRECTORIES(SYSTEM ${PYTHON_INCLUDE_PATH})

# Hide swig's horrible compiler warnings when building release.
IF(CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))
  SET_SOURCE_FILES_PROPERTIES(pyhextPYTHON_wrap.cxx PROPERTIES COMPILE_FLAGS -w)
ENDIF(CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))

SET_SOURCE_FILES_PROPERTIES(hext.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(hext python hext.i swig-html.cpp swig-rule.cpp)
SWIG_LINK_LIBRARIES(hext hext ${PYTHON_LIBRARIES})


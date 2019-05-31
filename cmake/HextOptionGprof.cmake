# Option GPROF, default OFF
# GNU gprof build

option(GPROF "gprof build" OFF)
if(GPROF)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg") 
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
endif()


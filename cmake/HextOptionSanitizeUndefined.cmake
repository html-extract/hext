# Option SANITIZEUNDEFINED, default OFF
# Adds -fsanitize=undefined and -fno-omit-frame-pointer to compiler flags

option(SANITIZEUNDEFINED "add -fsanitize=undefined and -fno-omit-frame-pointer" OFF)
if(SANITIZEUNDEFINED)
  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fno-omit-frame-pointer")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
endif(SANITIZEUNDEFINED)


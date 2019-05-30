# Option TCMALLOC, default OFF
# Link ${HEXT_LINK_TCMALLOC_TARGET} with libtcmalloc.

if(NOT HEXT_LINK_TCMALLOC_TARGET)
  # If you hit this error you forgot to set HEXT_LINK_TCMALLOC_TARGET
  # in your CMakeLists.txt. Set it to the name of the target you want to link
  # libtcmalloc with.
  message(FATAL_ERROR "HEXT_LINK_TCMALLOC_TARGET not set. Cannot add option TCMALLOC.")
else(NOT HEXT_LINK_TCMALLOC_TARGET)
  option(TCMALLOC "Link with libtcmalloc" OFF)
  if(TCMALLOC)
    target_link_libraries(${HEXT_LINK_TCMALLOC_TARGET} tcmalloc)

    # -fno-omit-frame-pointer must be set if you configured gperftools with
    # --enable-frame-pointers
    #ADD_DEFINITIONS("-fno-omit-frame-pointer")

    # force gcc to use tcmalloc
    if(CMAKE_COMPILER_IS_GNUCXX)
      add_definitions(
        "-fno-builtin-malloc" "-fno-builtin-calloc"
        "-fno-builtin-realloc" "-fno-builtin-free")
    endif(CMAKE_COMPILER_IS_GNUCXX)
  endif(TCMALLOC)
endif(NOT HEXT_LINK_TCMALLOC_TARGET)


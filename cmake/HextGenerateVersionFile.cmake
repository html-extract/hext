IF(NOT HEXT_VERSION_FILE_SOURCE)
  # If you hit this error you forgot to set HEXT_VERSION_FILE_SOURCE
  # in your CMakeLists.txt. Set it to the name of the input file you want to
  # use to generate the version file.
  MESSAGE(FATAL_ERROR "HEXT_VERSION_FILE_SOURCE not set. Cannot generate version file.")
ELSE(NOT HEXT_VERSION_FILE_SOURCE)
  INCLUDE(GetGitRevisionDescription)
  get_git_head_revision(GIT_REFSPEC PROJECT_VERSION_GIT_SHA1)

  # Short sha1 is good enough
  STRING(SUBSTRING ${PROJECT_VERSION_GIT_SHA1} 0 7 PROJECT_VERSION_GIT_SHA1)

  # The target file
  # Note: we cannot use GET_FILENAME_COMPONENT here, it strips all extensions.
  STRING(REGEX REPLACE ".in$" "" HEXT_VERSION_FILE_TARGET ${HEXT_VERSION_FILE_SOURCE})

  CONFIGURE_FILE(
    ${HEXT_VERSION_FILE_SOURCE}
    ${HEXT_VERSION_FILE_TARGET}
    @ONLY)

ENDIF(NOT HEXT_VERSION_FILE_SOURCE)


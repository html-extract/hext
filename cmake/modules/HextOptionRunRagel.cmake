# Option RUNRAGEL, default OFF
# If ON, Parser.h and Parser.cpp will be generated. Files are only
# written if they would actually change (or else we would have to recompile
# everytime). Linux only.

OPTION(RUNRAGEL "Call run_ragel.sh to generate the parser" OFF)
IF(RUNRAGEL)
  # ADD_CUSTOM_COMMAND is unsuitable, because there is no (non-hackish) way to
  # force cmake to run it on every call to make.
  # The best way for now is to manually call cmake every time there is a change
  # in the parser.
  EXECUTE_PROCESS(
    COMMAND
    "${PROJECT_SOURCE_DIR}/scripts/run_ragel.sh"
    "${PROJECT_SOURCE_DIR}/libhext/ragel/Parser.h.rl"
    "${PROJECT_SOURCE_DIR}/libhext/include/hext/Parser.h")
  EXECUTE_PROCESS(
    COMMAND
    "${PROJECT_SOURCE_DIR}/scripts/run_ragel.sh"
    "${PROJECT_SOURCE_DIR}/libhext/ragel/Parser.cpp.rl"
    "${PROJECT_SOURCE_DIR}/libhext/src/Parser.cpp")
ENDIF(RUNRAGEL)


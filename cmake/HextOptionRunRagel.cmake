# Option RUNRAGEL, default OFF
# If ON, Parser.cpp will be generated. File is only written if it would actually
# change (or else we would have to recompile everytime).

OPTION(RUNRAGEL "Call run_ragel.sh to generate the parser" OFF)
IF(RUNRAGEL)
  # ADD_CUSTOM_COMMAND is unsuitable, because there is no (non-hackish) way to
  # force cmake to run it on every call to make.
  # The best way for now is to manually call cmake every time there is a change
  # in the parser.
  EXECUTE_PROCESS(
    COMMAND
    "${PROJECT_SOURCE_DIR}/scripts/run_ragel.sh"
    "${PROJECT_SOURCE_DIR}/ragel/Parser.cpp.rl"
    "${PROJECT_SOURCE_DIR}/src/Parser.cpp")
ENDIF(RUNRAGEL)


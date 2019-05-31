# Option RUNRAGEL, default OFF
# If ON, Parser.cpp will be generated. File is only written if it would actually
# change (or else we would have to recompile everytime).

option(RUNRAGEL "Call run-ragel.sh to generate the parser" OFF)
if(RUNRAGEL)
  # ADD_CUSTOM_COMMAND is unsuitable, because there is no (non-hackish) way to
  # force cmake to run it on every call to make.
  # The best way for now is to manually call cmake every time there is a change
  # in the parser.
  execute_process(
    COMMAND
    "${PROJECT_SOURCE_DIR}/scripts/run-ragel.sh"
    "${PROJECT_SOURCE_DIR}/ragel/Parser.cpp.rl"
    "${PROJECT_SOURCE_DIR}/src/Parser.cpp")
endif()


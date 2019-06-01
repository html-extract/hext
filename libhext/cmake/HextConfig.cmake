include(CMakeFindDependencyMacro)
find_dependency(Boost COMPONENTS regex)
find_dependency(Gumbo)
include("${CMAKE_CURRENT_LIST_DIR}/HextTargets.cmake")

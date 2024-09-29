# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/oop-e-retake-cotoirares_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/oop-e-retake-cotoirares_autogen.dir/ParseCache.txt"
  "oop-e-retake-cotoirares_autogen"
  )
endif()

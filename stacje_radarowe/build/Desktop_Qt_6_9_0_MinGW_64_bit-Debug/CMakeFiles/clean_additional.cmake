# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\stacje_radarowe_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\stacje_radarowe_autogen.dir\\ParseCache.txt"
  "stacje_radarowe_autogen"
  )
endif()

# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\mainwindow_lib_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\mainwindow_lib_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\stacje_radarowe_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\stacje_radarowe_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\tests_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\tests_autogen.dir\\ParseCache.txt"
  "mainwindow_lib_autogen"
  "stacje_radarowe_autogen"
  "tests_autogen"
  )
endif()

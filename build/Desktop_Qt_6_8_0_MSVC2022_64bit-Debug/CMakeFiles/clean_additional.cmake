# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\WaterReminder_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\WaterReminder_autogen.dir\\ParseCache.txt"
  "WaterReminder_autogen"
  )
endif()

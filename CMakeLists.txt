### Google configuration
add_subdirectory("googletest")
### End of Google configuration

cmake_minimum_required(VERSION 3.10)

message("==== myApp Cmake Generation ====")

# set the project name
project(myApp VERSION 0.0.1)

if (CMAKE_CXX_PLATFORM_ID STREQUAL "MinGW")
  # PATCH for building Google Test using MiMinGW.org GCC-8.2.0-5) 8.2.0
  target_compile_options(gtest PUBLIC "-Wno-error=deprecated-declarations")
endif()

# add the executable
add_executable(myApp test.cpp myApp.cpp)

target_link_libraries(myApp gtest_main)

# Manage tests
enable_testing()
add_test(NAME my_test COMMAND myApp --gtest_output=xml)

# Specify the C++ standard
set_target_properties(myApp
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED True
)

# Add compile and link options to generate coverage data
target_compile_options(myApp PUBLIC "-g" "-fprofile-arcs" "-ftest-coverage")
target_link_options(myApp PUBLIC "-g" "-fprofile-arcs" "-ftest-coverage")

# Create custom cmake target to generate html coverage repport
if (UNIX)
  message(STATUS "Running on Linux")
  add_custom_target(myCoverage bash ${CMAKE_SOURCE_DIR}//lcov.sh ${CMAKE_BINARY_DIR}//CMakeFiles//myApp.dir)
elseif(WIN32)
  message(STATUS "Running on Windows")
  add_custom_target(myCoverage ${CMAKE_SOURCE_DIR}//lcov.bat ${CMAKE_BINARY_DIR}//CMakeFiles//myApp.dir)
else(UNIX)
  message(WARNING "Running on unknow target")
endif (UNIX)

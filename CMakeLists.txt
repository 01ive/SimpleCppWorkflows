### Google configuration
# From https://github.com/google/googletest

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()


# Now simply link against gtest or gtest_main as needed. Eg

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
add_executable(myApp myApp.cpp)

target_link_libraries(myApp gtest_main)

# Manage tests
enable_testing()
add_test(NAME my_test COMMAND myApp --gtest_output=xml)

# specify the C++ standard
set_target_properties(myApp
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED True
)

target_compile_options(myApp PUBLIC "-g" "-fprofile-arcs" "-ftest-coverage")
target_link_options(myApp PUBLIC "-g" "-fprofile-arcs" "-ftest-coverage")

if (UNIX)
  message(STATUS "Running on Linux")
  add_custom_target(myCoverage ./lcov.sh ${CMAKE_BINARY_DIR}//CMakeFiles//myApp.dir)
elseif(WIN32)
  message(STATUS "Running on Windows")
  add_custom_target(myCoverage ${CMAKE_SOURCE_DIR}//lcov.bat ${CMAKE_BINARY_DIR}//CMakeFiles//myApp.dir)
else(UNIX)
  message(WARNING "Running on unknow target")
endif (UNIX)
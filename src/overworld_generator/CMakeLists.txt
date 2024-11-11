# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name
project(OverworldGenerator)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source files
set(SOURCE_FILES
    ./src/main.cc
    ./src/drunkards_walk.cc
    ./src/create_map_png.cc
)

# Add the executable
add_executable(overworld_generator ${SOURCE_FILES})
add_executable(drunkards_walk_test
    ./src/drunkards_walk.cc
    ./src/test/drunkards_walk_test.cc)

# Add external libraries
target_include_directories(overworld_generator PRIVATE ./src/lib)
target_include_directories(drunkards_walk_test PRIVATE ./src/lib)

# Set the output directory for the executable
set_target_properties(overworld_generator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../executables"
)
#set_target_properties(drunkards_walk_test PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY "../tests"
#)

# Add testing support
enable_testing()

# Link tests with the executable
add_test(NAME DrunkardsWalkTest COMMAND drunkards_walk_test)
#set_target_properties(drunkards_walk_test PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY "../executables"
#)
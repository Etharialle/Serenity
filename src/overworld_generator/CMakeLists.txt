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

# Add external libraries
target_include_directories(overworld_generator PRIVATE ./lib)

# Set the output directory for the executable
set_target_properties(overworld_generator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../executables"
)
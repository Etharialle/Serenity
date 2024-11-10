# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name
project(OverworldGenerator)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(overworld_generator ./src/overworld_generator.cc)

# Set the output directory for the executable
set_target_properties(overworld_generator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../executables"
)
cmake_minimum_required (VERSION 2.6)

set(CMAKE_BUILD_TYPE Release)
project (hard-sphere-mc)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(hsmc.out src/main.cpp src/data_structures.cpp src/helpers.cpp src/mc_moves.cpp)

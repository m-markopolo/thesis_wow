cmake_minimum_required(VERSION 3.6.0)

project(perco.out 
  VERSION 1.0
  LANGUAGES CXX
)

add_executable(perco.out
  grid_operations.cpp
  main.cpp
  union_find.cpp
)

target_compile_features(perco.out
PRIVATE
cxx_std_17
)

target_compile_options(perco.out
PRIVATE
-Ofast
-march=native
-Wall
-Wextra
-Wpedantic
)

target_include_directories(perco.out
PRIVATE
/usr/include/eigen3/
)

project(perco_DEBUG.out 
  VERSION 1.0
  LANGUAGES CXX
)

add_executable(perco_DEBUG.out
  grid_operations.cpp
  main.cpp
  union_find.cpp
)

target_compile_features(perco_DEBUG.out
PRIVATE
cxx_std_17
)

target_compile_options(perco_DEBUG.out
PRIVATE
-O0
-pg
-g3
-Wall
-Wextra
-Wpedantic
)

target_include_directories(perco_DEBUG.out
PRIVATE
/usr/include/eigen3/
)

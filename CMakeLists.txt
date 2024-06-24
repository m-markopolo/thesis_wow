cmake_minimum_required(VERSION 3.6.0)

project(perco.out 
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(perco.out
  ./src/grid_operations.cpp
  ./src/main.cpp
  ./src/union_find.cpp
  ./src/solver.cpp
)
target_compile_features(perco.out
PRIVATE
cxx_std_17
)

target_compile_options(perco.out
PRIVATE
-Ofast
-march=native
-mtune=native
-Wall
-Wextra
-Wpedantic
)
target_include_directories(perco.out
PRIVATE
/usr/include/eigen3/
./src/
./include
./unit_tests/
)
  project(perco_DEBUG.out 
    VERSION 1.0
    LANGUAGES CXX
  )

  add_executable(perco_DEBUG.out
    ./src/grid_operations.cpp
    ./src/main.cpp
   ./src/union_find.cpp
   ./src/solver.cpp
  )

  target_compile_features(perco_DEBUG.out
  PRIVATE
  cxx_std_17
  )

  target_compile_options(perco_DEBUG.out
  PRIVATE
  -Og
  -pg
  -g3
  -Wall
  -Wextra
  -Wpedantic
  )

  target_include_directories(perco_DEBUG.out
  PRIVATE
  /usr/include/eigen3/
  ./src/
  ./include
  ./unit_tests/
  )

  project(perco_DEBUG.out 
    VERSION 1.0
    LANGUAGES CXX
  )

  set(EXEC_NAME manual_checks )

  add_executable( ${EXEC_NAME}
    ./src/grid_operations.cpp
    ./src/manual_checks.cpp
  )

  target_compile_features( ${EXEC_NAME}
  PRIVATE
  cxx_std_17
  )

  target_compile_options( ${EXEC_NAME}
  PRIVATE
  -O0
  -pg
  -g3
  -Wall
  -Wextra
  -Wpedantic
  )



  target_include_directories( ${EXEC_NAME}
  PRIVATE
  /usr/include/eigen3/
  /usr/include/catch2/
  ./include
  ./src/
  ./unit_tests/
  )

set(EXEC_NAME auto_tests )

find_package(Catch2 3 REQUIRED)
add_executable( ${EXEC_NAME}
  ./src/grid_operations.cpp
  ./unit_tests/grid_operations.t.cpp
  ./src/union_find.cpp
)
target_link_libraries(${EXEC_NAME} PRIVATE Catch2::Catch2WithMain)

target_compile_features( ${EXEC_NAME}
PRIVATE
cxx_std_17
)

target_compile_options( ${EXEC_NAME}
PRIVATE
-O0
-pg
-g3
-Wall
-Wextra
-Wpedantic
)



target_include_directories( ${EXEC_NAME}
PRIVATE
/usr/include/eigen3/
/usr/include/catch2/
./include
./src/
./unit_tests/
)

cmake_minimum_required(VERSION 3.10)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find SDL2
find_package(SDL2 REQUIRED)

# Include directories
include_directories(include)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(test)  # For Catch2 headers

# Source files - Main Executable
set(SOURCES
    src/main.cpp
    src/board.cpp
    src/piece.cpp
    src/move.cpp
    src/move_generator.cpp
)

# Create the main executable
add_executable(ChessEngine ${SOURCES})
target_link_libraries(ChessEngine ${SDL2_LIBRARIES})

# # --- Unit Tests ---
#
# # 1. Create a library for Catch2
# add_library(Catch2 STATIC test/catch_amalgamated.hpp)
# set_target_properties(Catch2 PROPERTIES LINKER_LANGUAGE CXX)  # <-- ADD THIS LINE
#
# # 2. Create the test executable, linking against Catch2 and our code
# add_executable(move_generator_tests test/move_generator_tests.cpp)
# target_link_libraries(move_generator_tests
#     Catch2        # Link against the Catch2 library
#     ${SDL2_LIBRARIES} # SDL2 (if your tests use it)
# )
#
# # Optional:  Make tests easily runnable with 'make test'
# enable_testing()
# add_test(NAME MoveGeneratorTests COMMAND move_generator_tests)

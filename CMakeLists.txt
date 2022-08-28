cmake_minimum_required(VERSION 3.23.2)

project(
    mychie
    VERSION 0.0.1
    LANGUAGES CXX
    )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Start Fetch ---
include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG 9.1.0
    )
FetchContent_MakeAvailable(fmt)
# --- Stop Fetch ---

option(CMAKE_EXPORT_COMPILE_COMMANDS "generate compile_commands.json" ON)

add_subdirectory(./core)
add_subdirectory(./test)

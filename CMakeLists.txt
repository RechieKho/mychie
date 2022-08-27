cmake_minimum_required(VERSION 3.23.2)

project(
    mychie
    VERSION 0.0.1
    LANGUAGES CXX
    )

option(CMAKE_EXPORT_COMPILE_COMMANDS "generate compile_commands.json" ON)

add_subdirectory(./core)
add_subdirectory(./test)

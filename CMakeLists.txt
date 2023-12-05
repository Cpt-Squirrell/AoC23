cmake_minimum_required(VERSION 3.12)
project(AoC23)

file(GLOB DAY_SOURCES "${CMAKE_SOURCE_DIR}/days/*.cpp")

add_executable(AoC23 "${DAY_SOURCES}" main.cpp)

set_property(TARGET AoC23 PROPERTY CXX_STANDARD 20)

add_custom_command(TARGET AoC23 POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/input_data" "${CMAKE_BINARY_DIR}/$<CONFIG>/input_data")
cmake_minimum_required(VERSION 3.12)
project(AoC23)

set(DAY_SOURCES "days/day.cpp"
                "days/d_one.cpp"
                "days/d_two.cpp"
                "days/d_three.cpp"
                "days/d_four.cpp")

add_executable(AoC23 "${DAY_SOURCES}" main.cpp)

set_property(TARGET AoC23 PROPERTY CXX_STANDARD 20)

if (MSVC)
    add_custom_command(TARGET AoC23 POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_directory 
            "${CMAKE_SOURCE_DIR}/input_data"
            "${CMAKE_BINARY_DIR}/$<CONFIG>/input_data")
else()
    add_custom_command(TARGET AoC23 POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_directory 
            "${CMAKE_SOURCE_DIR}/input_data"
            "${CMAKE_BINARY_DIR}/input_data")
endif()
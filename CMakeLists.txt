project(scripts_c)

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)

if (UNIX)
    set(CMAKE_CXX_FLAGS " -pthread ")
endif ()

add_subdirectory(algorithm)
add_subdirectory(cpp_object_model)
add_subdirectory(operation_system)
add_subdirectory(utils)
add_executable(scripts_c main.cpp)
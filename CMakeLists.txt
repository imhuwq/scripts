project(scripts_c)

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(algorithm/compute_prime)
add_subdirectory(algorithm/find_element_range)
add_subdirectory(operation_system/signal_interruption)
add_subdirectory(operation_system/concurrency)
add_subdirectory(utils/show_bits)
add_executable(scripts_c main.cpp operation_system/concurrency/fork_example.cpp)
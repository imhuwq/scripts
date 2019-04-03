project(scripts_c)
cmake_minimum_required(VERSION 3.12)

add_subdirectory(algorithm/compute_prime)
add_subdirectory(algorithm/find_element_range)
add_subdirectory(utils/show_bits)
add_executable(scripts_c main.cpp)
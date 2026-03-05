cmake_minimum_required(VERSION 3.10)

project(embedded-mastery-kit VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the subdirectories
add_subdirectory(01-c-fundamentals)
add_subdirectory(02-math-bitwise-operations)
add_subdirectory(03-algorithms-data-structures)
add_subdirectory(04-design-patterns)
add_subdirectory(05-communication-protocols)
add_subdirectory(06-rtos-fundamentals)

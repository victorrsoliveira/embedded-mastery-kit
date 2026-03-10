cmake_minimum_required(VERSION 3.10)

project(design_patterns C)

## Add the executable
add_executable(fsm
    fsm/fsm.c
    fsm/test_fsm.c)

target_include_directories(fsm PUBLIC fsm)

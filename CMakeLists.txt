cmake_minimum_required(VERSION 3.20)

project(lc3-vm)

add_library(lc3 
    src/lc3vm.c 
    src/lc3vm.h 
    src/utils.h
    src/utils.c
)

add_executable(lc3tests
    test/instructions.c
    test/program.c
    test/unit_tests.c
    dependencies/munit/munit.c
)

target_include_directories(lc3tests PRIVATE 
    dependencies/munit 
    src
)

target_link_libraries(lc3tests PRIVATE lc3)

enable_testing()

add_test(NAME lc3tests COMMAND $<TARGET_FILE:lc3tests>)
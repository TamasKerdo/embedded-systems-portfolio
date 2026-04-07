cmake_minimum_required(VERSION 3.16)

project(stm32_workspace C)

add_executable(firmware src/main.c)
add_executable(test tests/test_main.c)

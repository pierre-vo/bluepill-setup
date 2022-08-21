cmake_minimum_required(VERSION 3.23)

# set the project name and version
project(stm
        DESCRIPTION "STM + CMSIS parts"
        VERSION 1.0
        LANGUAGES C)


add_library(stm STATIC
    src/core_cm3.c
    src/system_stm32f10x.c
)

target_include_directories(stm PUBLIC inc)

# NOTE: Resetting only needed if you have a global CMAKE_CXX_CLANG_TIDY
set_target_properties(
    stm
    PROPERTIES
        C_CLANG_TIDY ""
)
cmake_minimum_required(VERSION 3.23)

# set the project name and version
project(CMSIS
        DESCRIPTION "CMSIS"
        VERSION 1.0
        LANGUAGES C)

add_library(CMSIS STATIC
    Device/ST/stm32f1xx/Source/system_stm32f1xx.c
)

target_include_directories(CMSIS PUBLIC
    Device/ST/stm32f1xx/Include
    CMSIS/Core/Include
)

target_include_directories(CMSIS INTERFACE
    Device/ST/stm32f1xx/Include
)

# NOTE: Resetting only needed if you have a global CMAKE_CXX_CLANG_TIDY
set_target_properties(
    CMSIS
    PROPERTIES
        C_CLANG_TIDY ""
)
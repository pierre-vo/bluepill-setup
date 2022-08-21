cmake_minimum_required(VERSION 3.23)

# set the project name and version
project(bluepill-base
        DESCRIPTION "bluepill-base"
        VERSION 1.0
        LANGUAGES C ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_CLANG_TIDY clang-tidy -p build/compile_commands.json -checks=-*,clang-analyzer-*,readability-*) # clang-diagnostic-*
add_compile_options(-Wall -Wextra -pedantic) # -Werror

set(LINK_SCRIPT "${CMAKE_SOURCE_DIR}/libs/stm/stm32f.ld")

# Cross-compiling settings
# set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/arm-toolchain.cmake")
set(CMAKE_EXE_LINKER_FLAGS "-T ${LINK_SCRIPT}")
set(CMAKE_C_FLAGS "-ffreestanding -nostdlib -mthumb -mcpu=cortex-m3")
set(CMAKE_C_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_C_IMPLICIT_LINK_DIRECTORIES "")


# add the executable
add_executable(${PROJECT_NAME}.elf
        src/main.c
        libs/stm/startup.s
)

target_include_directories(${PROJECT_NAME}.elf PUBLIC inc)

target_compile_definitions(${PROJECT_NAME}.elf PUBLIC STM32F102xB)

# add_subdirectory(libs/stm)
# target_link_libraries(${PROJECT_NAME}.elf PUBLIC stm)

add_subdirectory(external/stm32f1xx_hal_driver)
target_link_libraries(${PROJECT_NAME}.elf PUBLIC stm32f1xx_hal_driver)
target_compile_definitions(stm32f1xx_hal_driver PUBLIC STM32F102xB)

add_subdirectory(external/CMSIS)
target_link_libraries(${PROJECT_NAME}.elf PUBLIC CMSIS)
target_compile_definitions(CMSIS PUBLIC STM32F102xB)

# Set the target's compiler options
#target_compile_options(${PROJECT_NAME}.elf PRIVATE --cpu=Cortex-M4 --fpu=VFPv4_sp --dlib_config normal)
target_compile_options(${PROJECT_NAME}.elf PRIVATE -ffreestanding -nostdlib -mthumb -mcpu=cortex-m3)
   
# Set the target's linker options
#target_link_options(${PROJECT_NAME}.elf PRIVATE --semihosting --config ${TOOLKIT_DIR}/config/linker/ST/stm32f407xG.icf)

set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINK_DEPENDS "${LINK_SCRIPT}")
set_target_properties(${PROJECT_NAME}.elf PROPERTIES SUFFIX "")
#add_custom_command(TARGET ${PROJECT_NAME}.elf.elf POST_BUILD COMMAND "${ARM_GCC_BIN_DIR}/arm-none-eabi-objcopy" -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)

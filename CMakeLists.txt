cmake_minimum_required(VERSION 3.23)

# set the project name and version
project(bluepill-base
        DESCRIPTION "bluepill-base"
        VERSION 1.0
        LANGUAGES C ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_C_CLANG_TIDY clang-tidy -p build/compile_commands.json -checks=-*,clang-analyzer-*,readability-*) # clang-diagnostic-*
add_compile_options(-Wall -Wextra -pedantic) # -Werror

set(LINK_SCRIPT "${CMAKE_SOURCE_DIR}/STM32F103VBIx_FLASH.ld")

# Cross-compiling settings
# set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/arm-toolchain.cmake")
set(CMAKE_EXE_LINKER_FLAGS "-T ${LINK_SCRIPT}")
set(CMAKE_C_FLAGS "-ffreestanding -nostdlib -mthumb -mcpu=cortex-m3")
set(CMAKE_C_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_C_IMPLICIT_LINK_DIRECTORIES "")


# add the executable
add_executable(${PROJECT_NAME}.elf
        src/main.c
        src/stm32f1xx_hal_msp.c
        src/system_stm32f1xx.c
        startup_stm32f103xb.s
)

target_include_directories(${PROJECT_NAME}.elf PUBLIC inc)
target_compile_definitions(${PROJECT_NAME}.elf PUBLIC STM32F103xB)

# add_subdirectory(libs/stm)
# target_link_libraries(${PROJECT_NAME}.elf PUBLIC stm)

#add_subdirectory(external/stm32f1xx_hal_driver)
#target_link_libraries(${PROJECT_NAME}.elf PUBLIC stm32f1xx_hal_driver)
#target_compile_definitions(stm32f1xx_hal_driver PUBLIC STM32F103xB)

#add_subdirectory(external/CMSIS)
#target_link_libraries(${PROJECT_NAME}.elf PUBLIC CMSIS)
#target_compile_definitions(CMSIS PUBLIC STM32F103xB)

### STM32CubeF1

### BSP
add_library(BSP STATIC
    BSP/STM32F1xx_Nucleo/stm32f1xx_nucleo.c
)
target_include_directories(BSP PUBLIC
    inc
    BSP/STM32F1xx_Nucleo
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Inc
    external/STM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx/Include
    external/STM32CubeF1/Drivers/CMSIS/Include
)

# NOTE: Resetting only needed if you have a global CMAKE_CXX_CLANG_TIDY
set_target_properties(
    BSP
    PROPERTIES
        C_CLANG_TIDY ""
)

target_link_libraries(${PROJECT_NAME}.elf PUBLIC BSP)
target_compile_definitions(BSP PUBLIC STM32F103xB)


#### HAL
# set the project name and version
# project(stm32f1xx_hal_driver
#         DESCRIPTION "STM HAL driver"
#         VERSION 1.0
#         LANGUAGES C)

add_library(stm32f1xx_hal_driver STATIC
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_can.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cec.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_crc.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dac.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dac_ex.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_eth.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_hcd.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2s.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_irda.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_iwdg.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_mmc.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_msp_template.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_nand.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_nor.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pccard.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd_ex.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rtc.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rtc_ex.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_sd.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_smartcard.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_sram.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_timebase_rtc_alarm_template.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_timebase_tim_template.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_usart.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_wwdg.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_adc.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_crc.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_dac.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_dma.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_exti.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_fsmc.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_gpio.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_i2c.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_pwr.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_rcc.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_rtc.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_sdmmc.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_spi.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_tim.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_usart.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_usb.c
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_utils.c
)

target_include_directories(stm32f1xx_hal_driver PUBLIC
    inc
    external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Inc
    external/STM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx/Include
    external/STM32CubeF1/Drivers/CMSIS/Include
)

# NOTE: Resetting only needed if you have a global CMAKE_CXX_CLANG_TIDY
set_target_properties(
    stm32f1xx_hal_driver
    PROPERTIES
        C_CLANG_TIDY ""
)

target_link_libraries(${PROJECT_NAME}.elf PUBLIC stm32f1xx_hal_driver)
target_compile_definitions(stm32f1xx_hal_driver PUBLIC STM32F103xB)


#### CMSIS





### Compile

# Set the target's compiler options
#target_compile_options(${PROJECT_NAME}.elf PRIVATE --cpu=Cortex-M4 --fpu=VFPv4_sp --dlib_config normal)
target_compile_options(${PROJECT_NAME}.elf PRIVATE -ffreestanding -nostdlib -mthumb -mcpu=cortex-m3)
   
# Set the target's linker options
#target_link_options(${PROJECT_NAME}.elf PRIVATE --semihosting --config ${TOOLKIT_DIR}/config/linker/ST/stm32f407xG.icf)

#set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINK_DEPENDS "${LINK_SCRIPT}")
set_target_properties(${PROJECT_NAME}.elf PROPERTIES SUFFIX "")
#add_custom_command(TARGET ${PROJECT_NAME}.elf.elf POST_BUILD COMMAND "${ARM_GCC_BIN_DIR}/arm-none-eabi-objcopy" -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)

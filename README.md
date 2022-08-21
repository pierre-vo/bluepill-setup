# bluepill-setup
Set up code for bluepill HW

## Goals

### C
- no OS
- BMP
- SWO
- RTT


### C + freeRTOS

### C + chibios

### Rust

## Compile

`cmake -Bbuild -G "Unix Makefiles" --toolchain arm-toolchain.cmake`

## Temporary notes


## Links
- https://github.com/montoyo/bluepill-base
- https://github.com/fabiovila/bluepill-freertos
- HAL taken from: https://github.com/STMicroelectronics/stm32f1xx_hal_driver
    - 2022-04-22 [34bbf373db7327e32c98fd5e6f2ab03ed11949d0](https://github.com/STMicroelectronics/stm32f1xx_hal_driver/tree/34bbf373db7327e32c98fd5e6f2ab03ed11949d0)
- CMSIS st files taken from https://github.com/modm-io/cmsis-header-stm32
    - 2022-07-05 [362dba64ef52d1e1d75b224f2bf6537065b28869](https://github.com/modm-io/cmsis-header-stm32/tree/362dba64ef52d1e1d75b224f2bf6537065b28869)
- CMSIS files taken from https://github.com/ARM-software/CMSIS_5
    - 2022-08-19 [e2b3ec292061c42a2ddd6f76186fab5917e1fd66](https://github.com/ARM-software/CMSIS_5/tree/e2b3ec292061c42a2ddd6f76186fab5917e1fd66)
- https://github.com/STMicroelectronics/STM32CubeF1/blob/master/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
- https://github.com/STMicroelectronics/STM32CubeF1
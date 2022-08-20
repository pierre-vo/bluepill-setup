cmake_minimum_required(VERSION 3.23)

# set the project name and version
project(ModernCMakeExample
        DESCRIPTION "Example project"
        VERSION 1.0
        LANGUAGES C)


# add the executable
add_executable(MyMainExe
        src/main.c
)

target_include_directories(MyMainExe PUBLIC inc)

# Set the target's compiler options
#target_compile_options(MyMainExe PRIVATE --cpu=Cortex-M4 --fpu=VFPv4_sp --dlib_config normal)   
   
# Set the target's linker options
#target_link_options(MyMainExe PRIVATE --semihosting --config ${TOOLKIT_DIR}/config/linker/ST/stm32f407xG.icf)
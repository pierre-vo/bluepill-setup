# bluepill-setup
Set up code for bluepill HW


## Notes

mkdir build
cd build
cmake ../ -G "MinGW Makefiles"
cmake ../ -G "MSYS Makefiles"
cmake --build .



cmake ../ -D"CMAKE_MAKE_PROGRAM:PATH=C:/App/msys64/usr/bin/make.exe" -G "MSYS Makefiles"


```
cmake_minimum_required(VERSION 3.0.0)
project(MainTest VERSION 0.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_C_CLANG_TIDY clang-tidy -checks=-*,clang-diagnostic-*,clang-analyzer-*,readability-*)
add_compile_options(-Wall -Wextra -pedantic -Werror)
add_executable(MainTest src/main.c)
```

`cmake -B_builds -G "Ninja Multi-Config" --toolchain /path/to/xxx-toolchain.cmake`

`cmake -B_builds -G "Ninja Multi-Config" --toolchain xxx-toolchain.cmake`


https://github.com/montoyo/bluepill-base

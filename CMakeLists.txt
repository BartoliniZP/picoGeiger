cmake_minimum_required(VERSION 3.19)

include(pico_sdk_import.cmake)

pico_sdk_init()

project(PiPicoGeiger LANGUAGES C CXX)

set(CMAKE_BUILD_TYPE "Debug") 		#MODE

file(GLOB_RECURSE files CONFIGURE_DEPENDS src/*.cpp)

add_executable(geiger ${files})

target_link_libraries(geiger PRIVATE pico_stdlib hardware_i2c)

pico_enable_stdio_usb(geiger 1)
pico_enable_stdio_uart(geiger 0) 

pico_add_extra_outputs(geiger)

target_compile_options(geiger PRIVATE -std=c++20 -Wall -Wextra -Wpedantic -march=armv6-m -fno-exceptions)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_options(geiger PRIVATE -Og)
	target_compile_definitions(geiger PRIVATE _DEBUG_MODE) #for preprocessor
else()
	target_compile_options(geiger PRIVATE -O3)
endif()
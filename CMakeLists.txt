# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "E:/work/rasp-pico/pico-sdk")

# Pull in Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(FT8Transceiver C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 0)
set(PICO_CXX_ENABLE_RTTI 0)
set(PICO_NO_BINARY_INFO 0)

# Initialise the Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(FT8Transceiver FT8Transceiver.cpp )
add_subdirectory(JTEncode)
add_subdirectory(si5351a)

pico_set_program_name(FT8Transceiver "FT8Transceiver")
pico_set_program_version(FT8Transceiver "0.1")

pico_enable_stdio_uart(FT8Transceiver 0)
pico_enable_stdio_usb(FT8Transceiver 1)

# Add the standard library to the build
target_link_libraries(FT8Transceiver pico_stdlib)

# Add any user requested libraries
target_link_libraries(FT8Transceiver
        hardware_i2c
        )

target_link_libraries(FT8Transceiver
        JTEncode
	si5351a
        )

pico_add_extra_outputs(FT8Transceiver)


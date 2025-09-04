# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(AWGReplacment4CH C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(AWGReplacment4CH 
                patterns.c
                DMAs.c
                AWGReplacment4CH.c )

pico_set_program_name(AWGReplacment4CH "AWGReplacment4CH")
pico_set_program_version(AWGReplacment4CH "0.1")

# Generate PIO header
pico_generate_pio_header(AWGReplacment4CH ${CMAKE_CURRENT_LIST_DIR}/sync.pio)
pico_generate_pio_header(AWGReplacment4CH ${CMAKE_CURRENT_LIST_DIR}/rst.pio)
pico_generate_pio_header(AWGReplacment4CH ${CMAKE_CURRENT_LIST_DIR}/SVBsync.pio)
pico_generate_pio_header(AWGReplacment4CH ${CMAKE_CURRENT_LIST_DIR}/dac0.pio)
pico_generate_pio_header(AWGReplacment4CH ${CMAKE_CURRENT_LIST_DIR}/dac1.pio)
pico_generate_pio_header(AWGReplacment4CH ${CMAKE_CURRENT_LIST_DIR}/dac2.pio)
pico_generate_pio_header(AWGReplacment4CH ${CMAKE_CURRENT_LIST_DIR}/dac3.pio)
pico_generate_pio_header(AWGReplacment4CH ${CMAKE_CURRENT_LIST_DIR}/dac4.pio)
pico_generate_pio_header(AWGReplacment4CH ${CMAKE_CURRENT_LIST_DIR}/rstChan.pio)
pico_generate_pio_header(AWGReplacment4CH ${CMAKE_CURRENT_LIST_DIR}/SVB.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(AWGReplacment4CH 0)
pico_enable_stdio_usb(AWGReplacment4CH 1)

# Add the standard library to the build
target_link_libraries(AWGReplacment4CH
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(AWGReplacment4CH PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(AWGReplacment4CH 
        hardware_i2c
        hardware_dma
        hardware_pio
        hardware_clocks
        hardware_vreg
        hardware_irq
        )

pico_add_extra_outputs(AWGReplacment4CH)


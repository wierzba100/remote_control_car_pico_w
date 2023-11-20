cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(remote_control_car C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_BOARD pico_w CACHE STRING "Board type")

pico_sdk_init()

message("Running makefsdata python script")
execute_process(COMMAND
    py makefsdata.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

set(FILES
    main.c

        )

add_executable(${PROJECT_NAME} ${FILES})

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )

target_link_libraries(${PROJECT_NAME}
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
    pico_stdlib
    hardware_gpio
)

pico_add_extra_outputs(${PROJECT_NAME})
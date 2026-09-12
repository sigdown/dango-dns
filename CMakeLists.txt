cmake_minimum_required(VERSION 3.20)

project(dango LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


function(enable_dev_flags target)

    target_compile_options(${target} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -g
        -O0
        -fsanitize=address,undefined
    )

    target_link_options(${target} PRIVATE
        -fsanitize=address,undefined
    )

endfunction()


# core lib

add_library(dango_lib

    src/buffer.c
    src/dns.c
    src/io.c
    src/net.c

)

target_include_directories(dango_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# app
add_executable(dango

    src/main.c
    src/cli.c

)

target_link_libraries(dango
    PRIVATE
        dango_lib
)

enable_dev_flags(dango)


# test

enable_testing()

add_subdirectory(tests)